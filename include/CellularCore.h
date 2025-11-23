/* CellularCore.h
 * Central coordinator for the cellular network. Manages multiple cell towers,
 * routes messages, and collects network statistics.
 * C++17
 */
#ifndef CELLULAR_CORE_H
#define CELLULAR_CORE_H

#include "CellTower.h"

/**
 * @brief Lightweight message structure used by the CellularCore message queue.
 */
struct Message {
    int messageId;       ///< Unique message identifier
    int fromDeviceId;    ///< Origin device ID
    int toTowerId;       ///< Destination tower ID
    bool isVoice;        ///< True if voice (circuit), false if data (packet)
    char payload[256];   ///< Message payload
};

/**
 * @brief Central network coordinator class.
 *
 * The CellularCore manages multiple `CellTower` instances, a fixed-size
 * message queue, and statistics such as total messages processed.
 */
class CellularCore {
public:
    static constexpr int MAX_TOWERS = 100;
    static constexpr int MAX_MESSAGES = 100000;

private:
    int coreId_;
    CellTower* towers_[MAX_TOWERS];
    int towerCount_;
    Message* messageQueue_;
    int messageQueueSize_;
    long long totalMessagesProcessed_;

public:
    /**
     * @brief Construct a new CellularCore.
     * @param coreId Identifier for this core
     */
    CellularCore(int coreId);

    /**
     * @brief Destructor. Cleans up towers.
     */
    ~CellularCore();

    // Non-copyable
    CellularCore(const CellularCore&) = delete;
    CellularCore& operator=(const CellularCore&) = delete;

    // Non-movable
    CellularCore(CellularCore&&) = delete;
    CellularCore& operator=(CellularCore&&) = delete;

    /**
     * @brief Add a new cell tower to the core.
     * @param tower Pointer to the tower to add
     * @return true if added, false if tower is null or core at capacity
     */
    bool addCellTower(CellTower* tower);

    /**
     * @brief Retrieve a tower by ID.
     * @param towerId Identifier of the tower
     * @return pointer to tower or nullptr if not found
     */
    CellTower* getCellTower(int towerId) const;

    /**
     * @brief Generate and enqueue a message.
     * @param fromDeviceId Source device ID
     * @param toTowerId Destination tower ID
     * @param isVoice Type of message (voice/data)
     * @param payload Optional payload text (up to 255 chars)
     * @return true if enqueued, false if queue full
     */
    bool generateMessage(int fromDeviceId, int toTowerId, bool isVoice, const char* payload = "");

    /**
     * @brief Process all messages currently in the queue.
     * Routes messages to destination towers and updates statistics.
     */
    void processMessages();

    /**
     * @brief Get total messages processed.
     */
    long long getTotalMessagesProcessed() const { return totalMessagesProcessed_; }
    
    /**
     * @brief Get number of towers in core.
     */
    int getTowerCount() const { return towerCount_; }
};

#endif // CELLULAR_CORE_H
