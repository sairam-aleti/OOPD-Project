/* CellularCore.h
 * Central coordinator for the cellular network. Manages multiple cell towers,
 * routes messages, and collects network statistics.
 * C++17
 */
#ifndef CELLULAR_CORE_H
#define CELLULAR_CORE_H

#include "CellTower.h"

struct Message {
    int messageId;
    int fromDeviceId;
    int toTowerId;
    bool isVoice;
    char payload[256];
};

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
    CellularCore(int coreId);
    ~CellularCore();

    CellularCore(const CellularCore&) = delete;
    CellularCore& operator=(const CellularCore&) = delete;
    CellularCore(CellularCore&&) = delete;
    CellularCore& operator=(CellularCore&&) = delete;

    bool addCellTower(CellTower* tower);
    CellTower* getCellTower(int towerId) const;
    bool generateMessage(int fromDeviceId, int toTowerId, bool isVoice, const char* payload = "");
    void processMessages();

    long long getTotalMessagesProcessed() const { return totalMessagesProcessed_; }
    int getTowerCount() const { return towerCount_; }
};

#endif // CELLULAR_CORE_H
