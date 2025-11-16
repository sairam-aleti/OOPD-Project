/* CellularCore.h
 * Central coordinator for the cellular network. Manages multiple cell towers,
 * routes messages, and collects network statistics.
 * C++17
 */
#ifndef CELLULAR_CORE_H
#define CELLULAR_CORE_H

#include <memory>
#include <map>
#include <vector>
#include <string>
#include <mutex>

#include "CellTower.h"

/**
 * @brief Lightweight message structure used by the CellularCore message queue.
 */
struct Message {
    int messageId;       ///< Unique message identifier
    int fromDeviceId;    ///< Origin device ID
    int toTowerId;       ///< Destination tower ID
    bool isVoice;        ///< True if voice (circuit), false if data (packet)
    std::string payload; ///< Message payload (informational)
};

/**
 * @brief Central network coordinator class.
 *
 * The CellularCore manages multiple `CellTower` instances, a message queue,
 * and statistics such as total messages processed. All public methods are
 * exception-safe and use smart pointers for ownership.
 */
class CellularCore {
private:
    int coreId_;
    std::map<int, std::shared_ptr<CellTower>> towers_; ///< towerId -> tower
    std::vector<Message> messageQueue_;                 ///< simple FIFO queue
    long long totalMessagesProcessed_ = 0;
    mutable std::mutex queueMutex_;

public:
    /**
     * @brief Construct a new CellularCore.
     * @param coreId Identifier for this core
     */
    CellularCore(int coreId);

    ~CellularCore() = default;

    // Non-copyable
    CellularCore(const CellularCore&) = delete;
    CellularCore& operator=(const CellularCore&) = delete;

    // Movable
    CellularCore(CellularCore&&) = default;
    CellularCore& operator=(CellularCore&&) = default;

    /**
     * @brief Add a new cell tower to the core.
     * @param tower Shared pointer to the tower to add
     * @throw std::invalid_argument if tower is null or already exists
     */
    void addCellTower(std::shared_ptr<CellTower> tower);

    /**
     * @brief Retrieve a tower by ID.
     * @param towerId Identifier of the tower
     * @return shared_ptr<CellTower> or nullptr if not found
     */
    std::shared_ptr<CellTower> getCellTower(int towerId) const;

    /**
     * @brief Generate and enqueue a message.
     * @param fromDeviceId Source device ID
     * @param toTowerId Destination tower ID
     * @param isVoice Type of message (voice/data)
     * @param payload Optional payload text
     */
    void generateMessage(int fromDeviceId, int toTowerId, bool isVoice, const std::string& payload = "");

    /**
     * @brief Process all messages currently in the queue.
     * Routes messages to destination towers and updates statistics.
     */
    void processMessages();

    /**
     * @brief Get a brief status of the network coordinated by this core.
     * @return String describing core ID, towers, and messages processed
     */
    std::string getNetworkStatus() const;

    /**
     * @brief Get total messages processed.
     */
    long long getTotalMessagesProcessed() const { return totalMessagesProcessed_; }
};

#endif // CELLULAR_CORE_H
