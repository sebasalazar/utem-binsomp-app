#include "pgPool.h"

PGPool::PGPool() {
    std::lock_guard<std::mutex> localLocker(localMutex);

    for (int i = 0; i < POOL_SIZE; i++) {
        localPoll.emplace(std::make_shared<pqxx::lazyconnection>());
    }
}

PGPool::PGPool(std::string url) {
    std::lock_guard<std::mutex> localLocker(localMutex);

    for (int i = 0; i < POOL_SIZE; i++) {
        localPoll.emplace(std::make_shared<pqxx::lazyconnection>(url));
    }
}

std::shared_ptr<pqxx::lazyconnection> PGPool::connection() {
    std::unique_lock<std::mutex> localLock(localMutex);

    // if pool is empty, then wait until it notifies back
    while (localPoll.empty()) {
        localCondition.wait(localLock);
    }

    // get new connection in queue
    auto connection = localPoll.front();
    // immediately pop as we will use it now
    localPoll.pop();

    return connection;
}

void PGPool::freeConnection(std::shared_ptr<pqxx::lazyconnection> connection) {
    std::unique_lock<std::mutex> localLock(localMutex);

    // push a new connection into a pool
    localPoll.push(connection);

    // unlock mutex
    localLock.unlock();

    // notify one of thread that is waiting
    localCondition.notify_one();
}
