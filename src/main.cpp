#include "../include/basicIO.h"
#include "../include/CommunicationProtocol.h"
#include "../include/Protocol2G.h"
#include "../include/Protocol3G.h"
#include "../include/Protocol4G.h"
#include "../include/Protocol5G.h"
#include "../include/UserDevice.h"
#include "../include/CellTower.h"
#include "../include/CellularCore.h"

int main() {
    // Initialize core
    CellularCore core(1);

    // Instantiate protocols
    Protocol2G proto2g;
    Protocol3G proto3g;
    Protocol4G proto4g;
    Protocol5G proto5g;

    // Print capacities
    io.outputstring("=== Protocol Capacities ==="); io.terminate();

    io.outputstring(proto2g.getName()); io.outputstring(" - Max Users: "); io.outputint(proto2g.calculateMaxUsers()); io.terminate();
    io.outputstring("First channel users (2G): "); io.outputint(proto2g.getUsersPerChannel()); io.terminate();

    io.outputstring(proto3g.getName()); io.outputstring(" - Max Users: "); io.outputint(proto3g.calculateMaxUsers()); io.terminate();
    io.outputstring("First channel users (3G): "); io.outputint(proto3g.getUsersPerChannel()); io.terminate();

    io.outputstring(proto4g.getName()); io.outputstring(" - Max Users: "); io.outputint(proto4g.calculateMaxUsers()); io.terminate();
    io.outputstring("First channel users (4G, per antenna reuse): "); io.outputint(proto4g.getUsersPerChannel()); io.terminate();
    io.outputstring("4G required cores: "); io.outputint(proto4g.calculateRequiredCores()); io.terminate();

    io.outputstring(proto5g.getName()); io.outputstring(" - Max Users: "); io.outputint(proto5g.calculateMaxUsers()); io.terminate();
    io.outputstring("First channel users (5G): "); io.outputint(proto5g.getUsersPerChannel()); io.terminate();
    io.outputstring("5G required cores: "); io.outputint(proto5g.calculateRequiredCores()); io.terminate();

    // Create towers and add to core
    CellTower* tower2 = new CellTower(1, &proto2g);
    CellTower* tower3 = new CellTower(2, &proto3g);
    CellTower* tower4 = new CellTower(3, &proto4g);
    CellTower* tower5 = new CellTower(4, &proto5g);

    core.addCellTower(tower2);
    core.addCellTower(tower3);
    core.addCellTower(tower4);
    core.addCellTower(tower5);

    // Add a few sample devices to each tower (up to 5 or first-channel capacity)
    int addCount2 = proto2g.getUsersPerChannel() < 5 ? proto2g.getUsersPerChannel() : 5;
    int addCount3 = proto3g.getUsersPerChannel() < 5 ? proto3g.getUsersPerChannel() : 5;
    int addCount4 = (proto4g.getUsersPerChannel() < 5) ? proto4g.getUsersPerChannel() : 5;
    int addCount5 = (proto5g.getUsersPerChannel() < 5) ? proto5g.getUsersPerChannel() : 5;

    for (int i = 1; i <= addCount2; ++i) {
        UserDevice* d = new UserDevice(100 + i, 0, ConnectionType::DATA);
        tower2->addUserDevice(d);
        io.outputstring("2G: Added device "); io.outputint(d->getDeviceId()); io.outputstring(" assigned "); io.outputint(d->getAssignedFrequency()); io.terminate();
    }

    for (int i = 1; i <= addCount3; ++i) {
        UserDevice* d = new UserDevice(200 + i, 0, ConnectionType::DATA);
        tower3->addUserDevice(d);
        io.outputstring("3G: Added device "); io.outputint(d->getDeviceId()); io.outputstring(" assigned "); io.outputint(d->getAssignedFrequency()); io.terminate();
    }

    for (int i = 1; i <= addCount4; ++i) {
        UserDevice* d = new UserDevice(300 + i, 0, ConnectionType::DATA);
        tower4->addUserDevice(d);
        io.outputstring("4G: Added device "); io.outputint(d->getDeviceId()); io.outputstring(" assigned "); io.outputint(d->getAssignedFrequency()); io.terminate();
    }

    for (int i = 1; i <= addCount5; ++i) {
        UserDevice* d = new UserDevice(400 + i, 0, ConnectionType::DATA);
        tower5->addUserDevice(d);
        io.outputstring("5G: Added device "); io.outputint(d->getDeviceId()); io.outputstring(" assigned "); io.outputint(d->getAssignedFrequency()); io.terminate();
    }

    // Show users on first channel for each tower
    io.outputstring("\n=== Users on first channel per protocol ==="); io.terminate();
    int freq2 = proto2g.getFrequencyChannel(0);
    io.outputstring("2G first channel (kHz): "); io.outputint(freq2); io.terminate();
    io.outputstring("Users on 2G first channel: "); io.outputint(tower2->getUsersOnFrequency(freq2)); io.terminate();

    int freq3 = proto3g.getFrequencyChannel(0);
    io.outputstring("3G first channel (kHz): "); io.outputint(freq3); io.terminate();
    io.outputstring("Users on 3G first channel: "); io.outputint(tower3->getUsersOnFrequency(freq3)); io.terminate();

    int freq4 = proto4g.getFrequencyChannel(0);
    io.outputstring("4G first channel (kHz): "); io.outputint(freq4); io.terminate();
    io.outputstring("Users on 4G first channel: "); io.outputint(tower4->getUsersOnFrequency(freq4)); io.terminate();

    int freq5 = proto5g.getFrequencyChannel(0);
    io.outputstring("5G first channel (kHz): "); io.outputint(freq5); io.terminate();
    io.outputstring("Users on 5G first channel: "); io.outputint(tower5->getUsersOnFrequency(freq5)); io.terminate();

    // Generate some messages and process
    core.generateMessage(101, 1, false, "Hello from 2G device 101");
    core.generateMessage(201, 2, true, "Voice call from 3G device 201");
    core.generateMessage(301, 3, false, "Data packet from 4G device 301");
    core.generateMessage(401, 4, false, "Data packet from 5G device 401");

    io.outputstring("\nProcessing messages..."); io.terminate();
    core.processMessages();

    io.outputstring("\nSimulation complete.\n"); io.terminate();
    return 0;
}
