/* CommunicationProtocol.h
 * Abstract base for communication protocols (2G/3G/4G/5G)
 * C++17
 */
#ifndef COMMUNICATION_PROTOCOL_H
#define COMMUNICATION_PROTOCOL_H

/**
 * @brief Abstract base class defining the interface for communication protocols.
 *
 * Derived classes must implement protocol-specific constants and calculations.
 */
class CommunicationProtocol {
public:
    virtual ~CommunicationProtocol() = default;

    /// Human-readable protocol name ("2G", "3G", ...)
    virtual const char* getName() const = 0;

    /// Number of users supported per channel unit (semantics depend on protocol)
    virtual int getUsersPerChannel() const = 0;

    /// Channel bandwidth in kHz
    virtual int getChannelBandwidth() const = 0;

    /// Returns number of frequency channels managed by protocol
    virtual int getChannelCount() const = 0;

    /// Get channel by index (0 to getChannelCount()-1)
    virtual int getFrequencyChannel(int index) const = 0;

    /// Calculate maximum supported users for the whole spectrum
    virtual int calculateMaxUsers() const = 0;

    /**
     * @brief Calculate overhead messages for a given total messages count
     * @param totalMessages Total messages in the network
     * @return number of overhead messages
     */
    virtual int calculateOverhead(int totalMessages) const = 0;
};

#endif // COMMUNICATION_PROTOCOL_H
