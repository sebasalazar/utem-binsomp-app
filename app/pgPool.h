#ifndef PGPOOL_H
#define PGPOOL_H

#include <mutex>
#include <pqxx/pqxx>
#include <memory>
#include <condition_variable>
#include <queue>

class PGPool {
public:
    /**
     * Constructor vacío
     */
    PGPool();
    /**
     * Constructor con elementos de conexión
     * @param url texto con el formato de conexión para PostgreSQL
     */
    PGPool(std::string url);
    /**
     * 
     * @return Un puntero a una conexión
     */
    std::shared_ptr<pqxx::lazyconnection> connection();
    /**
     * Libera la conexión usada, la devuelve al pool
     * @param puntero de conexión
     */
    void freeConnection(std::shared_ptr<pqxx::lazyconnection>);

private:
    /**
     * Bloqueador con exclusión mutua.
     */
    std::mutex localMutex;
    
    /**
     * Semaforo de uso.
     */
    std::condition_variable localCondition;
    
    /**
     * Cola de conexión (pool propiamente tal)
     */
    std::queue<std::shared_ptr<pqxx::lazyconnection>> localPool;

    /**
     * Cantidad de conexiones que el programa mantiene abierta
     */
    const int POOL_SIZE = 10;
};

#endif
