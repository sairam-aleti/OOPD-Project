/* CellularCore.cpp
 * Implementation of CellularCore methods.
 */

#include "../include/CellularCore.h"
#include "../include/basicIO.h"

CellularCore::CellularCore(int coreId)
    : coreId_(coreId), towerCount_(0), messageQueueSize_(0), totalMessagesProcessed_(0) {
    // Initialize tower pointers
    for (int i = 0; i < MAX_TOWERS; ++i) {
        towers_[i] = nullptr;
    }
}

CellularCore::~CellularCore() {
    // Delete all towers
    for (int i = 0; i < towerCount_; ++i) {
        if (towers_[i]) {
            delete towers_[i];
            towers_[i] = nullptr;
        }
    }
}

bool CellularCore::addCellTower(CellTower* tower) {
    if (!tower) {
        io.outputstring("Error: Tower cannot be null");
        io.terminate();
        return false;
    }
    if (towerCount_ >= MAX_TOWERS) {
        io.outputstring("Error: Core at capacity: cannot add more towers");
        io.terminate();
        return false;
    }
    towers_[towerCount_] = tower;
    towerCount_++;
    return true;
}

CellTower* CellularCore::getCellTower(int towerId) const {
    for (int i = 0; i < towerCount_; ++i) {
        if (towers_[i] && towers_[i]->getTowerId() == towerId) {
            return towers_[i];
        }
    }
    return nullptr;
}

bool CellularCore::generateMessage(int fromDeviceId, int toTowerId, bool isVoice, const char* payload) {
    if (messageQueueSize_ >= MAX_MESSAGES) {
        io.outputstring("Error: Message queue full");
        io.terminate();
        return false;
    }
    
    int nextId = static_cast<int>(messageQueueSize_) + 1 + static_cast<int>(totalMessagesProcessed_);
    Message& m = messageQueue_[messageQueueSize_];
    m.messageId = nextId;
    m.fromDeviceId = fromDeviceId;
    m.toTowerId = toTowerId;
    m.isVoice = isVoice;
    
    if (payload) {
        // Copy payload safely
        for (int i = 0; i < 255 && payload[i] != '\0'; ++i) {
            m.payload[i] = payload[i];
        }
        m.payload[255] = '\0';
    } else {
        m.payload[0] = '\0';
    }
    
    messageQueueSize_++;
    return true;
}

void CellularCore::processMessages() {
    if (messageQueueSize_ == 0) {
        io.outputstring("[Core] No messages to process.");
        io.terminate();
        return;
    }

    int successCount = 0;
    int failureCount = 0;

    for (int i = 0; i < messageQueueSize_; ++i) {
        const Message& msg = messageQueue_[i];
        
        try {
            CellTower* tower = getCellTower(msg.toTowerId);
            if (!tower) {
                failureCount++;
                continue;
            }

            totalMessagesProcessed_++;
            successCount++;

        } catch (...) {
            failureCount++;
        }
    }
    
    io.outputstring("[Core] Successfully processed: ");
    io.outputint(successCount);
    io.outputstring(" messages\n");
    io.terminate();
    
    if (failureCount > 0) {
        io.outputstring("[Core] Failed to process: ");
        io.outputint(failureCount);
        io.outputstring(" messages\n");
        io.terminate();
    }
    
    // Clear message queue
    messageQueueSize_ = 0;
}
