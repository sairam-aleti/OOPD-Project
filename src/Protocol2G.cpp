/* Protocol2G.cpp
 * Implementation of Protocol2G methods.
 */

#include "../include/Protocol2G.h"

const char* Protocol2G::getName() const {
    return "2G (TDMA)";
}

int Protocol2G::getUsersPerChannel() const {
    return USERS_PER_200KHZ;
}

int Protocol2G::getChannelBandwidth() const {
    return CHANNEL_BANDWIDTH_KHZ;
}

int Protocol2G::getChannelCount() const {
    return TOTAL_SPECTRUM_KHZ / CHANNEL_BANDWIDTH_KHZ;
}

int Protocol2G::getFrequencyChannel(int index) const {
    if (index < 0 || index >= getChannelCount()) return -1;
    return index * CHANNEL_BANDWIDTH_KHZ;
}

int Protocol2G::calculateMaxUsers() const {
    int channels = TOTAL_SPECTRUM_KHZ / CHANNEL_BANDWIDTH_KHZ;
    return channels * USERS_PER_200KHZ;
}

int Protocol2G::calculateOverhead(int totalMessages) const {
    if (totalMessages <= 0) return 0;
    int overhead = (totalMessages * static_cast<int>(OVERHEAD_PERCENT)) / 100;
    return overhead;
}
