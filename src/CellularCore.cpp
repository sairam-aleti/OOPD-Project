/* CellularCore.cpp
 * Implementation of CellularCore methods.
 */

#include "../include/CellularCore.h"
#include "../include/Basicio.h"
#include <stdexcept>
#include <sstream>

CellularCore::CellularCore(int coreId)
    : coreId_(coreId), totalMessagesProcessed_(0) {}

void CellularCore::addCellTower(std::shared_ptr<CellTower> tower) {
    if (!tower) throw std::invalid_argument("Tower cannot be null");
    int id = tower->getTowerId();
    if (towers_.find(id) != towers_.end()) {
        throw std::invalid_argument("Tower with given ID already exists in core");
    }
    towers_.emplace(id, std::move(tower));
}

std::shared_ptr<CellTower> CellularCore::getCellTower(int towerId) const {
    auto it = towers_.find(towerId);
    if (it == towers_.end()) return nullptr;
    return it->second;
}

void CellularCore::generateMessage(int fromDeviceId, int toTowerId, bool isVoice, const std::string& payload) {
    std::lock_guard<std::mutex> lock(queueMutex_);
    int nextId = static_cast<int>(messageQueue_.size()) + 1 + static_cast<int>(totalMessagesProcessed_);
    Message m{ nextId, fromDeviceId, toTowerId, isVoice, payload };
    messageQueue_.push_back(std::move(m));
}

void CellularCore::processMessages() {
    // We'll process a snapshot to minimize lock hold time
    std::vector<Message> snapshot;
    {
        std::lock_guard<std::mutex> lock(queueMutex_);
        if (messageQueue_.empty()) {
            basicio_writeln("[Core] No messages to process.");
            return;
        }
        snapshot.swap(messageQueue_);
    }

    for (const auto &msg : snapshot) {
        try {
            auto tower = getCellTower(msg.toTowerId);
            if (!tower) {
                basicio_write("[Core] Message ");
                basicio_write_int(msg.messageId);
                basicio_writeln(" dropped: destination tower not found.");
                continue;
            }

            // For demonstration we simply increment processed count and print info
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

            // Optionally, we can calculate overhead for this tower's protocol
            try {
                const CommunicationProtocol* proto = tower->getProtocol();
                int overhead = proto->calculateOverhead(1); // per-message overhead estimate
                basicio_write("[Core] Protocol overhead estimate (per message): ");
                basicio_write_int(overhead);
                basicio_writeln(" messages");
            } catch (...) {
                basicio_writeln("[Core] Failed to calculate protocol overhead.");
            }

        } catch (const std::exception &ex) {
            basicio_write("[Core] Exception while processing message: ");
            basicio_writeln(ex.what());
        } catch (...) {
            basicio_writeln("[Core] Unknown exception while processing message.");
        }
    }
}

std::string CellularCore::getNetworkStatus() const {
    std::ostringstream oss;
    oss << "Core ID: " << coreId_ << " | Towers: " << towers_.size()
        << " | Total Messages Processed: " << totalMessagesProcessed_;
    return oss.str();
}
