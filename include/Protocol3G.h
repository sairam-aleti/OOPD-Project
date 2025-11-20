/* Protocol3G.h
 * 3G protocol (CDMA) implementation of CommunicationProtocol
 */
#ifndef PROTOCOL_3G_H
#define PROTOCOL_3G_H

#include "CommunicationProtocol.h"

/**
 * @brief 3G (CDMA) protocol implementation.
 */
class Protocol3G : public CommunicationProtocol {
public:
    static constexpr int USERS_PER_200KHZ = 32;
    static constexpr int CHANNEL_BANDWIDTH_KHZ = 200;
    static constexpr int TOTAL_SPECTRUM_KHZ = 1000;
    static constexpr int MESSAGES_PER_USER = 10; // combined data + voice
    static constexpr double OVERHEAD_PERCENT = 8.0; // percent per 100 messages

    const char* getName() const override;
    int getUsersPerChannel() const override;
    int getChannelBandwidth() const override;
    int getChannelCount() const override;
    int getFrequencyChannel(int index) const override;
    int calculateMaxUsers() const override;
    int calculateOverhead(int totalMessages) const override;
};

#endif // PROTOCOL_3G_H
