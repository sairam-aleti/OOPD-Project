/* CustomProtocol.h
 * Custom protocol implementation of CommunicationProtocol
 */
#ifndef CUSTOM_PROTOCOL_H
#define CUSTOM_PROTOCOL_H

#include "CommunicationProtocol.h"

/**
 * @brief Custom protocol implementation allowing user-defined parameters.
 */
class CustomProtocol : public CommunicationProtocol {
private:
    int usersPerChannel_;
    int channelBandwidth_;
    int totalSpectrum_;
    int messagesPerUser_;
    double overheadPercent_;

public:
    CustomProtocol(int usersPerChannel, int channelBandwidth, int totalSpectrum)
        : usersPerChannel_(usersPerChannel), 
          channelBandwidth_(channelBandwidth), 
          totalSpectrum_(totalSpectrum),
          messagesPerUser_(10), // Default
          overheadPercent_(0.0) {}

    const char* getName() const override { return "Custom Protocol"; }
    int getUsersPerChannel() const override { return usersPerChannel_; }
    int getChannelBandwidth() const override { return channelBandwidth_; }
    int getChannelCount() const override { return totalSpectrum_ / channelBandwidth_; }
    
    int getFrequencyChannel(int index) const override {
        if (index < 0 || index >= getChannelCount()) return -1;
        return index * channelBandwidth_;
    }
    
    int calculateMaxUsers() const override {
        return getChannelCount() * usersPerChannel_;
    }
    
    int calculateOverhead(int totalMessages) const override {
        if (totalMessages <= 0) return 0;
        return (totalMessages * static_cast<int>(overheadPercent_)) / 100;
    }
    
    void setOverheadPercent(double percent) { overheadPercent_ = percent; }
};

#endif // CUSTOM_PROTOCOL_H
