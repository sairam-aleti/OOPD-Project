/* CellTower.h
 * Represents a cellular tower managing multiple user devices.
 * C++17
 */
#ifndef CELL_TOWER_H
#define CELL_TOWER_H

#include "CommunicationProtocol.h"
#include "UserDevice.h"

/**
 * @brief Represents a cellular tower managing user devices and frequency allocation.
 *
 * Each tower uses a specific communication protocol and manages a fixed-size collection
 * of connected user devices. It allocates frequencies and tracks users per channel.
 */
class CellTower {
public:
    static constexpr int MAX_DEVICES = 100000;
    static constexpr int MAX_FREQ_KHZ = 100000;

private:
    int towerId_;
    const CommunicationProtocol* protocol_;
    UserDevice* devices_[MAX_DEVICES];
    int deviceCount_;
    int frequencyAllocation_[MAX_FREQ_KHZ + 1]; // frequency -> count of devices

    bool isFrequencyAtCapacity(int frequency) const;

public:
    CellTower(int towerId, const CommunicationProtocol* protocol);
    ~CellTower();

    CellTower(const CellTower&) = delete;
    CellTower& operator=(const CellTower&) = delete;
    CellTower(CellTower&&) = delete;
    CellTower& operator=(CellTower&&) = delete;

    int getTowerId() const { return towerId_; }
    const CommunicationProtocol* getProtocol() const { return protocol_; }
    int getDeviceCount() const { return deviceCount_; }
    int getUsersOnFrequency(int frequency) const;
    UserDevice* getDevice(int index) const;

    bool addUserDevice(UserDevice* device);
    bool removeUserDevice(int deviceId);
    bool allocateFrequency(UserDevice* device);
};

#endif // CELL_TOWER_H
