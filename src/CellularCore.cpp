/* CellularCore.cpp
 * Implementation of CellularCore methods.
 */

#include "../include/CellularCore.h"
#include "../include/Basicio.h"

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
        basicio_writeln("Error: Tower cannot be null");
        return false;
    }
    if (towerCount_ >= MAX_TOWERS) {
        basicio_writeln("Error: Core at capacity: cannot add more towers");
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
        basicio_writeln("Error: Message queue full");
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
        basicio_writeln("[Core] No messages to process.");
        return;
    }

    for (int i = 0; i < messageQueueSize_; ++i) {
        const Message& msg = messageQueue_[i];
        
        try {
            CellTower* tower = getCellTower(msg.toTowerId);
            if (!tower) {
                basicio_write("[Core] Message ");
                basicio_write_int(msg.messageId);
                basicio_writeln(" dropped: destination tower not found.");
                continue;
            }

            totalMessagesProcessed_++;

            // Output using Basicio functions only
            basicio_write("[Core] Processing message ");
            basicio_write_int(msg.messageId);
            basicio_write(" -> Tower ");
            basicio_write_int(msg.toTowerId);
            basicio_write(" | From Device ");
            basicio_write_int(msg.fromDeviceId);
            basicio_write(" | Type: ");
            basicio_writeln(msg.isVoice ? "VOICE" : "DATA");

            // Calculate protocol overhead
            const CommunicationProtocol* proto = tower->getProtocol();
            if (proto) {
                int overhead = proto->calculateOverhead(1);
                basicio_write("[Core] Protocol overhead estimate: ");
                basicio_write_int(overhead);
                basicio_writeln(" messages");
            }

        } catch (...) {
            basicio_writeln("[Core] Exception while processing message.");
        }
    }
    
    // Clear message queue
    messageQueueSize_ = 0;
}
