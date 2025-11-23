#include "../include/basicIO.h"
#include "../include/CommunicationProtocol.h"
#include "../include/Protocol2G.h"
#include "../include/Protocol3G.h"
#include "../include/Protocol4G.h"
#include "../include/Protocol5G.h"
#include "../include/CustomProtocol.h"
#include "../include/UserDevice.h"
#include "../include/CellTower.h"
#include "../include/CellularCore.h"

int main() {
    int choice = 0;
    
    while (1) {
        io.outputstring("\n========== Cellular Network Simulator ==========\n"); io.terminate();
        io.outputstring("Select a communication protocol:\n"); io.terminate();
        io.outputstring("1. 2G (TDMA)\n"); io.terminate();
        io.outputstring("2. 3G (CDMA)\n"); io.terminate();
        io.outputstring("3. 4G (OFDM)\n"); io.terminate();
        io.outputstring("4. 5G (Massive MIMO)\n"); io.terminate();
        io.outputstring("5. Custom Protocol\n"); io.terminate();
        io.outputstring("6. Exit\n"); io.terminate();
        io.outputstring("Enter choice (1-6): "); 
        choice = io.inputint();

        if (choice == 6) {
            io.outputstring("\nThank you for using Cellular Network Simulator. Exiting...\n"); io.terminate();
            break;
        }

        CellularCore core(1);
        CommunicationProtocol* protocol = nullptr;
        int towerId = 0;
        const char* protocolName = "";
        int usersPerChannel = 0;
        int channelBandwidth = 0;
        int totalSpectrum = 0;

        if (choice == 1) {
            protocol = new Protocol2G();
            protocolName = "2G (TDMA)";
            towerId = 1;
        } else if (choice == 2) {
            protocol = new Protocol3G();
            protocolName = "3G (CDMA)";
            towerId = 2;
        } else if (choice == 3) {
            protocol = new Protocol4G();
            protocolName = "4G (OFDM)";
            towerId = 3;
        } else if (choice == 4) {
            protocol = new Protocol5G();
            protocolName = "5G (Massive MIMO)";
            towerId = 4;
        } else if (choice == 5) {
            io.outputstring("\n========== Custom Protocol Configuration ==========\n"); io.terminate();
            
            io.outputstring("Enter users per channel: "); 
            usersPerChannel = io.inputint();
            
            io.outputstring("Enter channel bandwidth (kHz): "); 
            channelBandwidth = io.inputint();
            
            io.outputstring("Enter total spectrum (kHz): "); 
            totalSpectrum = io.inputint();
            
            if (channelBandwidth <= 0 || totalSpectrum <= 0 || usersPerChannel <= 0) {
                io.outputstring("\nInvalid custom protocol parameters. Returning to menu.\n"); io.terminate();
                continue;
            }

            if (channelBandwidth > totalSpectrum) {
                io.outputstring("\nError: Channel bandwidth cannot be larger than total spectrum.\n"); io.terminate();
                continue;
            }

            protocol = new CustomProtocol(usersPerChannel, channelBandwidth, totalSpectrum);
            protocolName = "Custom Protocol";
            towerId = 5;
            
            io.outputstring("\nCustom protocol created:\n"); io.terminate();
            io.outputstring("Users per channel: "); io.outputint(usersPerChannel); io.terminate();
            io.outputstring("Channel bandwidth (kHz): "); io.outputint(channelBandwidth); io.terminate();
            io.outputstring("Total spectrum (kHz): "); io.outputint(totalSpectrum); io.terminate();
            io.outputstring("(Overhead percentage will be asked after message count)\n"); io.terminate();
            
        } else {
            io.outputstring("\nInvalid choice. Returning to menu.\n"); io.terminate();
            continue;
        }

        // Display protocol information
        io.outputstring("\n========== "); io.outputstring(protocolName); io.outputstring(" Protocol Information ==========\n"); io.terminate();
        
        io.outputstring("Users per channel: "); io.outputint(protocol->getUsersPerChannel()); io.terminate();
        io.outputstring("Channel bandwidth (kHz): "); io.outputint(protocol->getChannelBandwidth()); io.terminate();
        io.outputstring("Number of channels: "); io.outputint(protocol->getChannelCount()); io.terminate();
        io.outputstring("Maximum users supported: "); io.outputint(protocol->calculateMaxUsers()); io.terminate();
        
        if (choice == 3 || choice == 4) {
             io.outputstring("Required Cellular Cores: "); io.outputint(protocol->calculateRequiredCores()); io.terminate();
        }

        // Get message quantity from user
        io.outputstring("\nEnter total number of messages to generate: "); 
        int totalMessages = io.inputint();

        // Get overhead percentage from user
        io.outputstring("Enter overhead percentage for this simulation (0-100): "); 
        int overheadPercent = io.inputint();
        
        if (overheadPercent < 0 || overheadPercent > 100) {
            io.outputstring("\nInvalid overhead percentage. Setting to 0.\n"); io.terminate();
            overheadPercent = 0;
        }

        // Calculate overhead
        if (choice == 5) {
             static_cast<CustomProtocol*>(protocol)->setOverheadPercent(static_cast<double>(overheadPercent));
        }
        int overheadMessages = (totalMessages * overheadPercent) / 100;
        
        io.outputstring("\n========== Overhead Calculation ==========\n"); io.terminate();
        io.outputstring("Total messages requested: "); io.outputint(totalMessages); io.terminate();
        io.outputstring("Overhead percentage: "); io.outputint(overheadPercent); io.outputstring("%\n"); io.terminate();
        io.outputstring("Overhead reduction: "); io.outputint(overheadMessages); io.outputstring(" messages reserved for overhead\n"); io.terminate();

        // Calculate max devices: reduce protocol capacity by overhead percentage
        int maxCapacity = protocol->calculateMaxUsers();
        int maxDevices = maxCapacity - ((maxCapacity * overheadPercent) / 100);
        
        if (maxCapacity > 0 && maxDevices < 1) maxDevices = 1;

        // Clamp to tower hardware limit
        if (maxDevices > CellTower::MAX_DEVICES) {
            io.outputstring("Note: Limiting devices to tower capacity of "); 
            io.outputint(CellTower::MAX_DEVICES); 
            io.outputstring("\n"); io.terminate();
            maxDevices = CellTower::MAX_DEVICES;
        }

        io.outputstring("Maximum devices after overhead reduction: "); io.outputint(maxDevices); io.terminate();

        if (maxDevices <= 0) {
            io.outputstring("\nError: No devices can be supported with current configuration. Skipping simulation.\n"); io.terminate();
            if (protocol) delete protocol;
            continue;
        }

        // Create tower for this protocol
        CellTower* tower = new CellTower(towerId, protocol);
        
        core.addCellTower(tower);

        // Add devices to tower
        io.outputstring("\n========== Device Allocation ==========\n"); io.terminate();
        io.outputstring("Adding "); io.outputint(maxDevices); io.outputstring(" devices to tower...\n"); io.terminate();

        for (int i = 1; i <= maxDevices; ++i) {
            ConnectionType type = (i % 3 == 0) ? ConnectionType::VOICE : ConnectionType::DATA;
            int deviceId = 5000 + i;
            UserDevice* device = new UserDevice(deviceId, 0, type);
            tower->addUserDevice(device);
        }

        // Show first channel occupancy
        int firstChannelFreq = protocol->getFrequencyChannel(0);
        int firstChannelUsers = tower->getUsersOnFrequency(firstChannelFreq);
        
        io.outputstring("\nFirst channel frequency (kHz): "); 
        if (choice == 4) {
             // 5G: 1800 MHz base
             io.outputint(1800000 + firstChannelFreq);
        } else {
             io.outputint(firstChannelFreq);
        }
        io.terminate();
        io.outputstring("Users on first channel: "); io.outputint(firstChannelUsers); io.terminate();

        // Generate messages
        io.outputstring("\n========== Message Generation & Processing ==========\n"); io.terminate();
        io.outputstring("Generating "); io.outputint(totalMessages); io.outputstring(" messages...\n"); io.terminate();

        for (int i = 0; i < totalMessages && i < CellularCore::MAX_MESSAGES; ++i) {
            bool isVoice = (i % 4 == 0);
            int deviceId = 5000 + (i % maxDevices) + 1;
            core.generateMessage(deviceId, towerId, isVoice, isVoice ? "Voice call" : "Data packet");
        }

        io.outputstring("\nProcessing messages...\n"); io.terminate();
        core.processMessages();

        // Calculate message breakdown
        int voiceMessages = 0;
        int dataMessages = 0;
        for (int i = 0; i < totalMessages && i < CellularCore::MAX_MESSAGES; ++i) {
            if (i % 4 == 0) {
                voiceMessages++;
            } else {
                dataMessages++;
            }
        }

        io.outputstring("\n========== Simulation Complete ==========\n"); io.terminate();
        io.outputstring("Total messages processed: "); io.outputint(totalMessages); io.terminate();
        io.outputstring("  - Voice messages: "); io.outputint(voiceMessages); io.terminate();
        io.outputstring("  - Data messages: "); io.outputint(dataMessages); io.terminate();
        
        io.outputstring("Devices utilized: "); io.outputint(maxDevices); io.terminate();
        io.outputstring("Overhead incurred: "); io.outputint(overheadMessages); io.outputstring(" messages ("); io.outputint(overheadPercent); io.outputstring("%)\n"); io.terminate();
        
        io.outputstring("Channel Statistics:\n"); io.terminate();
        io.outputstring("  - First channel frequency (kHz): "); 
        if (choice == 4) {
             io.outputint(1800000 + firstChannelFreq);
        } else {
             io.outputint(firstChannelFreq);
        }
        io.terminate();
        io.outputstring("  - Users on first channel: "); io.outputint(firstChannelUsers); io.terminate();
        
        int maxChannelUsers = protocol->getUsersPerChannel();
        io.outputstring("  - Max capacity per channel: "); io.outputint(maxChannelUsers); io.terminate();
        
        if (protocol) {
            delete protocol;
            protocol = nullptr;
        }
    }

    return 0;
}
