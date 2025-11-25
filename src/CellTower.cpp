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
    for (int i = 0; i <= MAX_FREQ_KHZ; ++i) {
        frequencyAllocation_[i] = 0;
    }
    for (int i = 0; i < MAX_DEVICES; ++i) {
        devices_[i] = nullptr;
    }
}

CellTower::~CellTower() {
    for (int i = 0; i < deviceCount_; ++i) {
        if (devices_[i]) {
            delete devices_[i];
            devices_[i] = nullptr;
        }
    }
}

bool CellTower::isFrequencyAtCapacity(int frequency) const {
    if (frequency < 0 || frequency > MAX_FREQ_KHZ) return true;
    int usersOnFreq = frequencyAllocation_[frequency];
    int capacity = protocol_->getUsersPerChannel();
    return usersOnFreq >= capacity;
}

int CellTower::getUsersOnFrequency(int frequency) const {
    if (frequency < 0 || frequency > MAX_FREQ_KHZ) return 0;
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

    int channelCount = protocol_->getChannelCount();
    
    for (int i = 0; i < channelCount; ++i) {
        int freq = protocol_->getFrequencyChannel(i);
        if (freq >= 0 && freq <= MAX_FREQ_KHZ && !isFrequencyAtCapacity(freq)) {
            device->setAssignedFrequency(freq);
            frequencyAllocation_[freq]++;
            return true;
        }
    }
    return false;
}

bool CellTower::addUserDevice(UserDevice* device) {
    if (!device) {
        io.outputstring("Error: Device cannot be null");
        io.terminate();
        return false;
    }

    if (deviceCount_ >= MAX_DEVICES || deviceCount_ >= protocol_->calculateMaxUsers()) {
        io.outputstring("Error: Tower at capacity: cannot add more devices");
        return false;
    }

    if (!allocateFrequency(device)) {
        return false;
    }

    devices_[deviceCount_] = device;
    deviceCount_++;
    device->setConnected(true);
    return true;
}

bool CellTower::removeUserDevice(int deviceId) {
    for (int i = 0; i < deviceCount_; ++i) {
        if (devices_[i] && devices_[i]->getDeviceId() == deviceId) {
            int freq = devices_[i]->getAssignedFrequency();
            if (freq >= 0 && freq <= MAX_FREQ_KHZ) {
                frequencyAllocation_[freq]--;
            }

            devices_[i]->setConnected(false);

            for (int j = i; j < deviceCount_ - 1; ++j) {
                devices_[j] = devices_[j + 1];
            }
            devices_[deviceCount_ - 1] = nullptr;
            deviceCount_--;
            return true;
        }
    }
    return false;
}
