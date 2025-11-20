/* Protocol5G.cpp
 * Implementation of Protocol5G methods.
 */

#include "../include/Protocol5G.h"

const char* Protocol5G::getName() const {
    return "5G (Massive MIMO)";
}

int Protocol5G::getUsersPerChannel() const {
    return USERS_PER_1MHZ * ANTENNAS;
}

int Protocol5G::getChannelBandwidth() const {
    return CHANNEL_BANDWIDTH_KHZ;
}

int Protocol5G::getChannelCount() const {
    return TOTAL_SPECTRUM_KHZ / CHANNEL_BANDWIDTH_KHZ;
}

int Protocol5G::getFrequencyChannel(int index) const {
    if (index < 0 || index >= getChannelCount()) return -1;
    return FREQUENCY_BAND_MHZ * 1000 + index * CHANNEL_BANDWIDTH_KHZ;
}

int Protocol5G::calculateMaxUsers() const {
    int channels = TOTAL_SPECTRUM_KHZ / CHANNEL_BANDWIDTH_KHZ;
    return channels * USERS_PER_1MHZ * ANTENNAS;
}

int Protocol5G::calculateOverhead(int totalMessages) const {
    if (totalMessages <= 0) return 0;
    int overhead = (totalMessages * static_cast<int>(OVERHEAD_PERCENT)) / 100;
    return overhead;
}

int Protocol5G::calculateRequiredCores() const {
    int maxUsers = calculateMaxUsers();
    int cores = (maxUsers + USERS_PER_CORE - 1) / USERS_PER_CORE;
    return cores;
}
