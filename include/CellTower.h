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
private:
    static constexpr int MAX_DEVICES = 20000;
    
    int towerId_;
    const CommunicationProtocol* protocol_;
    UserDevice* devices_[MAX_DEVICES];
    int deviceCount_;
    int frequencyAllocation_[1001]; // frequency -> count of devices (index 0-1000 kHz)

    /**
     * @brief Check if a frequency channel is at capacity.
     * @param frequency Frequency to check
     * @return true if at capacity, false otherwise
     */
    bool isFrequencyAtCapacity(int frequency) const;

public:
    /**
     * @brief Construct a new CellTower.
     * @param towerId Unique tower identifier
     * @param protocol Pointer to communication protocol (not owned by tower)
     */
    CellTower(int towerId, const CommunicationProtocol* protocol);

    /**
     * @brief Destructor. Cleans up allocated devices.
     */
    ~CellTower();

    // Prevent copying
    CellTower(const CellTower&) = delete;
    CellTower& operator=(const CellTower&) = delete;

    // Prevent moving (due to raw pointers)
    CellTower(CellTower&&) = delete;
    CellTower& operator=(CellTower&&) = delete;

    // Getters
    /**
     * @brief Get the tower ID.
     * @return Unique tower identifier
     */
    int getTowerId() const { return towerId_; }

    /**
     * @brief Get the communication protocol used.
     * @return Const pointer to the protocol
     */
    const CommunicationProtocol* getProtocol() const { return protocol_; }

    /**
     * @brief Get number of connected devices.
     * @return Count of devices
     */
    int getDeviceCount() const { return deviceCount_; }

    /**
     * @brief Get number of users on a specific frequency.
     * @param frequency Frequency to check
     * @return Count of devices on that frequency
     */
    int getUsersOnFrequency(int frequency) const;

    /**
     * @brief Get device by index.
     * @param index Device index (0 to getDeviceCount()-1)
     * @return Pointer to device or nullptr if out of range
     */
    UserDevice* getDevice(int index) const;

    // Device management
    /**
     * @brief Add a new user device to the tower.
     * Automatically allocates a suitable frequency.
     * @param device Pointer to user device
     * @return true if added successfully, false if tower at capacity or allocation fails
     */
    bool addUserDevice(UserDevice* device);

    /**
     * @brief Remove a user device from the tower.
     * @param deviceId ID of device to remove
     * @return true if removed, false if not found
     */
    bool removeUserDevice(int deviceId);

    /**
     * @brief Allocate a suitable frequency for a device.
     * @param device User device to allocate frequency for
     * @return true if allocation successful, false if no available frequency
     */
    bool allocateFrequency(UserDevice* device);
};

#endif // CELL_TOWER_H
