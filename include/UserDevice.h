/* UserDevice.h
 * Represents a connected user device in the cellular network.
 * C++17
 */
#ifndef USER_DEVICE_H
#define USER_DEVICE_H

/**
 * @enum ConnectionType
 * @brief Type of connection for a user device.
 */
enum class ConnectionType {
    DATA,  ///< Data connection (packet switching)
    VOICE  ///< Voice connection (circuit switching)
};

/**
 * @brief Represents a single user device connected to the cellular network.
 *
 * Each device has a unique ID, assigned frequency, and connection type.
 * Data hiding ensures validation of all member access through public interface.
 */
class UserDevice {
private:
    int deviceId_;                  ///< Unique identifier for this device
    int assignedFrequency_;         ///< Assigned frequency in kHz
    ConnectionType connectionType_; ///< Type of connection (DATA or VOICE)
    bool isConnected_;              ///< Connection status

    /**
     * @brief Validate device ID and frequency values.
     * @throw Throws if validation fails (called from constructor/setters)
     */
    void validate() const;

public:
    /**
     * @brief Construct a new UserDevice.
     * @param deviceId Unique device identifier (must be positive)
     * @param frequency Assigned frequency in kHz (must be positive)
     * @param type Connection type (DATA or VOICE)
     */
    UserDevice(int deviceId, int frequency, ConnectionType type);

    /**
     * @brief Destructor.
     */
    ~UserDevice() = default;

    // Prevent copying
    UserDevice(const UserDevice&) = delete;
    UserDevice& operator=(const UserDevice&) = delete;

    // Allow move semantics
    UserDevice(UserDevice&&) = default;
    UserDevice& operator=(UserDevice&&) = default;

    // Getters
    /**
     * @brief Get the device ID.
     * @return Unique device identifier
     */
    int getDeviceId() const { return deviceId_; }

    /**
     * @brief Get the assigned frequency.
     * @return Frequency in kHz
     */
    int getAssignedFrequency() const { return assignedFrequency_; }

    /**
     * @brief Get the connection type.
     * @return ConnectionType (DATA or VOICE)
     */
    ConnectionType getConnectionType() const { return connectionType_; }

    /**
     * @brief Get connection status.
     * @return true if connected, false otherwise
     */
    bool isConnected() const { return isConnected_; }

    // Setters with validation
    /**
     * @brief Set the assigned frequency.
     * @param frequency New frequency in kHz (must be positive)
     */
    void setAssignedFrequency(int frequency);

    /**
     * @brief Set the connection type.
     * @param type New connection type
     */
    void setConnectionType(ConnectionType type) { connectionType_ = type; }

    /**
     * @brief Set connection status.
     * @param connected true to mark as connected, false to disconnect
     */
    void setConnected(bool connected) { isConnected_ = connected; }
};

#endif // USER_DEVICE_H
