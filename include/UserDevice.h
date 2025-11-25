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
    UserDevice(int deviceId, int frequency, ConnectionType type);
    ~UserDevice() = default;

    // Prevent copying
    UserDevice(const UserDevice&) = delete;
    UserDevice& operator=(const UserDevice&) = delete;

    // Allow move semantics
    UserDevice(UserDevice&&) = default;
    UserDevice& operator=(UserDevice&&) = default;

    int getDeviceId() const { return deviceId_; }
    int getAssignedFrequency() const { return assignedFrequency_; }
    ConnectionType getConnectionType() const { return connectionType_; }
    bool isConnected() const { return isConnected_; }

    void setAssignedFrequency(int frequency);
    void setConnectionType(ConnectionType type) { connectionType_ = type; }
    void setConnected(bool connected) { isConnected_ = connected; }
};

#endif // USER_DEVICE_H
