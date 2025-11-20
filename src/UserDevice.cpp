/* UserDevice.cpp
 * Implementation of UserDevice class.
 */

#include "../include/UserDevice.h"
#include "../include/basicIO.h"

void UserDevice::validate() const {
    if (deviceId_ <= 0) {
        io.outputstring("Error: Device ID must be positive");
        io.terminate();
    }
    if (assignedFrequency_ <= 0) {
        io.outputstring("Error: Assigned frequency must be positive");
        io.terminate();
    }
}

UserDevice::UserDevice(int deviceId, int frequency, ConnectionType type)
    : deviceId_(deviceId), assignedFrequency_(frequency), 
      connectionType_(type), isConnected_(true) {
    validate();
}

void UserDevice::setAssignedFrequency(int frequency) {
    if (frequency <= 0) {
        io.outputstring("Error: Assigned frequency must be positive");
        io.terminate();
        return;
    }
    assignedFrequency_ = frequency;
}
