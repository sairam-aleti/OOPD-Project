/* Protocol5G.h
 * 5G protocol (Massive MIMO at 1800 MHz) implementation of CommunicationProtocol
 */
#ifndef PROTOCOL_5G_H
#define PROTOCOL_5G_H

#include "CommunicationProtocol.h"

/**
 * @brief 5G (Massive MIMO at 1800 MHz) protocol implementation.
 */
class Protocol5G : public CommunicationProtocol {
public:
    static constexpr int FREQUENCY_BAND_MHZ = 1800;
    static constexpr int USERS_PER_1MHZ = 30;
    static constexpr int CHANNEL_BANDWIDTH_KHZ = 1000;
    static constexpr int TOTAL_SPECTRUM_KHZ = 10000;
    static constexpr int ANTENNAS = 16;
    static constexpr int MESSAGES_PER_USER = 10;
    static constexpr double OVERHEAD_PERCENT = 3.0;
    static constexpr int USERS_PER_CORE = 2000;

    const char* getName() const override;
    int getUsersPerChannel() const override;
    int getChannelBandwidth() const override;
    int getChannelCount() const override;
    int getFrequencyChannel(int index) const override;
    int calculateMaxUsers() const override;
    int calculateOverhead(int totalMessages) const override;

    int calculateRequiredCores() const override;
};

#endif // PROTOCOL_5G_H
