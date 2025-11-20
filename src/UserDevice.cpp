/* UserDevice.cpp
 * Implementation of UserDevice class.
 */

#include "../include/UserDevice.h"
#include "../include/Basicio.h"

void UserDevice::validate() const {
    if (deviceId_ <= 0) {
        basicio_writeln("Error: Device ID must be positive");
    }
    if (assignedFrequency_ <= 0) {
        basicio_writeln("Error: Assigned frequency must be positive");
    }
}

UserDevice::UserDevice(int deviceId, int frequency, ConnectionType type)
    : deviceId_(deviceId), assignedFrequency_(frequency), 
      connectionType_(type), isConnected_(true) {
    validate();
}

void UserDevice::setAssignedFrequency(int frequency) {
    if (frequency <= 0) {
        basicio_writeln("Error: Assigned frequency must be positive");
        return;
    }
    assignedFrequency_ = frequency;
}
