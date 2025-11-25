/* Protocol4G.h
 * 4G protocol (OFDM) implementation of CommunicationProtocol
 */
#ifndef PROTOCOL_4G_H
#define PROTOCOL_4G_H

#include "CommunicationProtocol.h"

/**
 * @brief 4G (OFDM) protocol implementation.
 */
class Protocol4G : public CommunicationProtocol {
public:
    static constexpr int USERS_PER_10KHZ = 30;
    static constexpr int CHANNEL_BANDWIDTH_KHZ = 10;
    static constexpr int TOTAL_SPECTRUM_KHZ = 1000;
    static constexpr int ANTENNAS = 4;
    static constexpr int MESSAGES_PER_USER = 10;
    static constexpr double OVERHEAD_PERCENT = 5.0;
    static constexpr int USERS_PER_CORE = 1000;

    const char* getName() const override;
    int getUsersPerChannel() const override;
    int getChannelBandwidth() const override;
    int getChannelCount() const override;
    int getFrequencyChannel(int index) const override;
    int calculateMaxUsers() const override;
    int calculateOverhead(int totalMessages) const override;

    int calculateRequiredCores() const override;
};

#endif // PROTOCOL_4G_H
