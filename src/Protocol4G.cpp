/* Protocol4G.cpp
 * Implementation of Protocol4G methods.
 */

#include "../include/Protocol4G.h"

const char* Protocol4G::getName() const {
    return "4G (OFDM)";
}

int Protocol4G::getUsersPerChannel() const {
    return USERS_PER_10KHZ * ANTENNAS;
}

int Protocol4G::getChannelBandwidth() const {
    return CHANNEL_BANDWIDTH_KHZ;
}

int Protocol4G::getChannelCount() const {
    return TOTAL_SPECTRUM_KHZ / CHANNEL_BANDWIDTH_KHZ;
}

int Protocol4G::getFrequencyChannel(int index) const {
    if (index < 0 || index >= getChannelCount()) return -1;
    return index * CHANNEL_BANDWIDTH_KHZ;
}

int Protocol4G::calculateMaxUsers() const {
    int channels = TOTAL_SPECTRUM_KHZ / CHANNEL_BANDWIDTH_KHZ;
    return channels * USERS_PER_10KHZ * ANTENNAS;
}

int Protocol4G::calculateOverhead(int totalMessages) const {
    if (totalMessages <= 0) return 0;
    int overhead = (totalMessages * static_cast<int>(OVERHEAD_PERCENT)) / 100;
    return overhead;
}

int Protocol4G::calculateRequiredCores() const {
    int maxUsers = calculateMaxUsers();
    int cores = (maxUsers + USERS_PER_CORE - 1) / USERS_PER_CORE;
    return cores;
}
