/* Protocol2G.h
 * 2G protocol (TDMA) implementation of CommunicationProtocol
 */
#ifndef PROTOCOL_2G_H
#define PROTOCOL_2G_H

#include "CommunicationProtocol.h"

/**
 * @brief 2G (TDMA) protocol implementation.
 */
class Protocol2G : public CommunicationProtocol {
public:
    static constexpr int USERS_PER_200KHZ = 16;
    static constexpr int CHANNEL_BANDWIDTH_KHZ = 200;
    static constexpr int TOTAL_SPECTRUM_KHZ = 1000;
    static constexpr int MESSAGES_PER_USER = 20; // 5 data + 15 voice
    static constexpr double OVERHEAD_PERCENT = 10.0; // percent per 100 messages

    const char* getName() const override;
    int getUsersPerChannel() const override;
    int getChannelBandwidth() const override;
    int getChannelCount() const override;
    int getFrequencyChannel(int index) const override;
    int calculateMaxUsers() const override;
    int calculateOverhead(int totalMessages) const override;
};

#endif // PROTOCOL_2G_H
