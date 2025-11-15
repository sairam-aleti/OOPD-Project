/* UserDevice.cpp
 * Implementation of UserDevice class.
 */

#include "../include/UserDevice.h"
#include <stdexcept>
#include <sstream>

void UserDevice::validate() const {
    if (deviceId_ <= 0) {
        throw std::invalid_argument("Device ID must be positive");
    }
    if (assignedFrequency_ <= 0) {
        throw std::invalid_argument("Assigned frequency must be positive");
    }
}

UserDevice::UserDevice(int deviceId, int frequency, ConnectionType type)
    : deviceId_(deviceId), assignedFrequency_(frequency), 
      connectionType_(type), isConnected_(true) {
    validate();
}

void UserDevice::setAssignedFrequency(int frequency) {
    if (frequency <= 0) {
        throw std::invalid_argument("Assigned frequency must be positive");
    }
    assignedFrequency_ = frequency;
}

std::string UserDevice::getDeviceInfo() const {
    std::ostringstream oss;
    oss << "Device ID: " << deviceId_ 
        << " | Frequency: " << assignedFrequency_ << " kHz"
        << " | Type: " << (connectionType_ == ConnectionType::DATA ? "DATA" : "VOICE")
        << " | Connected: " << (isConnected_ ? "YES" : "NO");
    return oss.str();
}
