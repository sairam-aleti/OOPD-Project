/* CellTower.cpp
 * Implementation of CellTower class.
 */

#include "../include/CellTower.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>

CellTower::CellTower(int towerId, std::shared_ptr<CommunicationProtocol> protocol)
    : towerId_(towerId), protocol_(protocol) {
    if (!protocol_) {
        throw std::invalid_argument("Protocol cannot be null");
    }
}

bool CellTower::isFrequencyAtCapacity(int frequency) const {
    auto it = frequencyAllocation_.find(frequency);
    if (it == frequencyAllocation_.end()) {
        return false; // Frequency not used yet
    }
    int usersOnFreq = it->second.size();
    int capacity = protocol_->getUsersPerChannel();
    return usersOnFreq >= capacity;
}

int CellTower::getUsersOnFrequency(int frequency) const {
    auto it = frequencyAllocation_.find(frequency);
    if (it == frequencyAllocation_.end()) {
        return 0;
    }
    return it->second.size();
}

void CellTower::allocateFrequency(std::shared_ptr<UserDevice> device) {
    if (!device) {
        throw std::invalid_argument("Device cannot be null");
    }

    // Get available frequencies from protocol
    auto channels = protocol_->getFrequencyChannels();
    
    // Find first frequency with available capacity
    for (int freq : channels) {
        if (!isFrequencyAtCapacity(freq)) {
            device->setAssignedFrequency(freq);
            frequencyAllocation_[freq].push_back(device->getDeviceId());
            return;
        }
    }
    
    // No frequency available
    throw std::runtime_error("No available frequency channels for device");
}

void CellTower::addUserDevice(std::shared_ptr<UserDevice> device) {
    if (!device) {
        throw std::invalid_argument("Device cannot be null");
    }

    // Check if max users exceeded
    if (devices_.size() >= static_cast<size_t>(protocol_->calculateMaxUsers())) {
        throw std::runtime_error("Tower at capacity: cannot add more devices");
    }

    // Allocate frequency
    allocateFrequency(device);

    // Add device to tower
    devices_.push_back(device);
    device->setConnected(true);
}

bool CellTower::removeUserDevice(int deviceId) {
    auto it = std::find_if(devices_.begin(), devices_.end(),
        [deviceId](const std::shared_ptr<UserDevice>& dev) {
            return dev->getDeviceId() == deviceId;
        });
    
    if (it == devices_.end()) {
        return false; // Device not found
    }

    // Remove from frequency allocation
    int freq = (*it)->getAssignedFrequency();
    auto& freqDevices = frequencyAllocation_[freq];
    auto freqIt = std::find(freqDevices.begin(), freqDevices.end(), deviceId);
    if (freqIt != freqDevices.end()) {
        freqDevices.erase(freqIt);
    }

    // Mark disconnected and remove from devices list
    (*it)->setConnected(false);
    devices_.erase(it);
    return true;
}

std::string CellTower::getTowerStatus() const {
    std::ostringstream oss;
    oss << "Tower ID: " << towerId_
        << " | Protocol: " << protocol_->getName()
        << " | Connected Devices: " << devices_.size()
        << " | Max Capacity: " << protocol_->calculateMaxUsers();
    return oss.str();
}
