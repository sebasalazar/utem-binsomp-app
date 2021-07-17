#ifndef PGPOOL_H
#define PGPOOL_H

#include <mutex>
#include <pqxx/pqxx>
#include <memory>
#include <condition_variable>
#include <queue>
#include <omp.h>

class PGPool {
public:
    PGPool();
    PGPool(std::string url);
    std::shared_ptr<pqxx::lazyconnection> connection();
    void freeConnection(std::shared_ptr<pqxx::lazyconnection>);

private:
    std::mutex localMutex;
    std::condition_variable localCondition;
    std::queue<std::shared_ptr<pqxx::lazyconnection>> localPoll;

    const int POOL_SIZE = 2 * omp_get_num_threads();
};

#endif
