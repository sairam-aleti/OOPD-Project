/* CellTower.h
 * Represents a cellular tower managing multiple user devices.
 * C++17
 */
#ifndef CELL_TOWER_H
#define CELL_TOWER_H

#include "CommunicationProtocol.h"
#include "UserDevice.h"
#include <memory>
#include <vector>
#include <map>

/**
 * @brief Represents a cellular tower managing user devices and frequency allocation.
 *
 * Each tower uses a specific communication protocol and manages a collection of
 * connected user devices. It allocates frequencies and tracks users per channel,
 * enforcing capacity limits based on protocol specifications.
 */
class CellTower {
private:
    int towerId_;                                      ///< Unique tower identifier
    std::shared_ptr<CommunicationProtocol> protocol_; ///< Protocol used by this tower
    std::vector<std::shared_ptr<UserDevice>> devices_; ///< Connected devices
    std::map<int, std::vector<int>> frequencyAllocation_; ///< Maps frequency -> device IDs

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
     * @param protocol Shared pointer to communication protocol
     */
    CellTower(int towerId, std::shared_ptr<CommunicationProtocol> protocol);

    /**
     * @brief Destructor.
     */
    ~CellTower() = default;

    // Prevent copying
    CellTower(const CellTower&) = delete;
    CellTower& operator=(const CellTower&) = delete;

    // Allow move semantics
    CellTower(CellTower&&) = default;
    CellTower& operator=(CellTower&&) = default;

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
    const CommunicationProtocol* getProtocol() const { return protocol_.get(); }

    /**
     * @brief Get number of connected devices.
     * @return Count of devices
     */
    int getDeviceCount() const { return devices_.size(); }

    /**
     * @brief Get number of users on a specific frequency.
     * @param frequency Frequency to check
     * @return Count of devices on that frequency
     */
    int getUsersOnFrequency(int frequency) const;

    /**
     * @brief Get all connected devices.
     * @return Reference to vector of device pointers
     */
    const std::vector<std::shared_ptr<UserDevice>>& getDevices() const { 
        return devices_; 
    }

    // Device management
    /**
     * @brief Add a new user device to the tower.
     * Automatically allocates a suitable frequency.
     * @param device Shared pointer to user device
     * @throw std::runtime_error if tower is at capacity or allocation fails
     */
    void addUserDevice(std::shared_ptr<UserDevice> device);

    /**
     * @brief Remove a user device from the tower.
     * @param deviceId ID of device to remove
     * @return true if removed, false if not found
     */
    bool removeUserDevice(int deviceId);

    /**
     * @brief Allocate a suitable frequency for a device.
     * @param device User device to allocate frequency for
     * @throw std::runtime_error if no available frequency
     */
    void allocateFrequency(std::shared_ptr<UserDevice> device);

    /**
     * @brief Get formatted tower status information.
     * @return String describing tower ID, protocol, device count, capacity
     */
    std::string getTowerStatus() const;
};

#endif // CELL_TOWER_H
