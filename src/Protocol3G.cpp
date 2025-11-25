/* Protocol3G.cpp
 * Implementation of Protocol3G methods.
 */

#include "../include/Protocol3G.h"

const char* Protocol3G::getName() const {
    return "3G (CDMA)";
}

int Protocol3G::getUsersPerChannel() const {
    return USERS_PER_200KHZ;
}

int Protocol3G::getChannelBandwidth() const {
    return CHANNEL_BANDWIDTH_KHZ;
}

int Protocol3G::getChannelCount() const {
    return TOTAL_SPECTRUM_KHZ / CHANNEL_BANDWIDTH_KHZ;
}

int Protocol3G::getFrequencyChannel(int index) const {
    if (index < 0 || index >= getChannelCount()) return -1;
    return index * CHANNEL_BANDWIDTH_KHZ;
}

int Protocol3G::calculateMaxUsers() const {
    int channels = TOTAL_SPECTRUM_KHZ / CHANNEL_BANDWIDTH_KHZ;
    return channels * USERS_PER_200KHZ;
}

int Protocol3G::calculateOverhead(int totalMessages) const {
    if (totalMessages <= 0) return 0;
    int overhead = static_cast<int>((totalMessages * OVERHEAD_PERCENT) / 100.0);
    return overhead;
}
