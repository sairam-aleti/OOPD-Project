/* CellTower.cpp
 * Implementation of CellTower class.
 */

#include "../include/CellTower.h"
#include "../include/basicIO.h"

CellTower::CellTower(int towerId, const CommunicationProtocol* protocol)
    : towerId_(towerId), protocol_(protocol), deviceCount_(0) {
    if (!protocol_) {
        io.outputstring("Error: Protocol cannot be null");
        io.terminate();
        return;
    }
    // Initialize frequency allocation
    for (int i = 0; i <= 1000; ++i) {
        frequencyAllocation_[i] = 0;
    }
    // Initialize device pointers
    for (int i = 0; i < MAX_DEVICES; ++i) {
        devices_[i] = nullptr;
    }
}

CellTower::~CellTower() {
    // Delete all allocated devices
    for (int i = 0; i < deviceCount_; ++i) {
        if (devices_[i]) {
            delete devices_[i];
            devices_[i] = nullptr;
        }
    }
}

bool CellTower::isFrequencyAtCapacity(int frequency) const {
    if (frequency < 0 || frequency > 1000) return true;
    int usersOnFreq = frequencyAllocation_[frequency];
    int capacity = protocol_->getUsersPerChannel();
    return usersOnFreq >= capacity;
}

int CellTower::getUsersOnFrequency(int frequency) const {
    if (frequency < 0 || frequency > 1000) return 0;
    return frequencyAllocation_[frequency];
}

UserDevice* CellTower::getDevice(int index) const {
    if (index < 0 || index >= deviceCount_) return nullptr;
    return devices_[index];
}

bool CellTower::allocateFrequency(UserDevice* device) {
    if (!device) {
        io.outputstring("Error: Device cannot be null");
        io.terminate();
        return false;
    }

    // Get available frequencies from protocol
    int channelCount = protocol_->getChannelCount();
    
    // Find first frequency with available capacity
    for (int i = 0; i < channelCount; ++i) {
        int freq = protocol_->getFrequencyChannel(i);
        if (freq >= 0 && freq <= 1000 && !isFrequencyAtCapacity(freq)) {
            device->setAssignedFrequency(freq);
            frequencyAllocation_[freq]++;
            return true;
        }
    }
    
    // No frequency available
    io.outputstring("Error: No available frequency channels for device");
    io.terminate();
    return false;
}

bool CellTower::addUserDevice(UserDevice* device) {
    if (!device) {
        io.outputstring("Error: Device cannot be null");
        io.terminate();
        return false;
    }

    // Check if max devices exceeded
    if (deviceCount_ >= MAX_DEVICES || deviceCount_ >= protocol_->calculateMaxUsers()) {
        io.outputstring("Error: Tower at capacity: cannot add more devices");
        io.terminate();
        return false;
    }

    // Allocate frequency
    if (!allocateFrequency(device)) {
        return false;
    }

    // Add device to tower
    devices_[deviceCount_] = device;
    deviceCount_++;
    device->setConnected(true);
    return true;
}

bool CellTower::removeUserDevice(int deviceId) {
    for (int i = 0; i < deviceCount_; ++i) {
        if (devices_[i] && devices_[i]->getDeviceId() == deviceId) {
            // Remove from frequency allocation
            int freq = devices_[i]->getAssignedFrequency();
            if (freq >= 0 && freq <= 1000) {
                frequencyAllocation_[freq]--;
            }

            // Mark disconnected
            devices_[i]->setConnected(false);

            // Shift remaining devices
            for (int j = i; j < deviceCount_ - 1; ++j) {
                devices_[j] = devices_[j + 1];
            }
            devices_[deviceCount_ - 1] = nullptr;
            deviceCount_--;
            return true;
        }
    }
    return false; // Device not found
}
