#ifndef DBSERVICE_H
#define DBSERVICE_H

#include "Bin.h"
#include "pgPool.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <thread>
#include <pqxx/pqxx>

class DBService {
public:
    DBService();
    DBService(std::string host, int port, std::string username, std::string password, std::string db);
    virtual ~DBService();
    std::string GetDb() const;
    void SetDb(std::string db);
    std::string GetHost() const;
    void SetHost(std::string host);
    std::string GetPassword() const;
    void SetPassword(std::string password);
    int GetPort() const;
    void SetPort(int port);
    std::string GetUsername() const;
    void SetUsername(std::string username);

    /// Consultas
    std::string GetVersion() const;
    Bin GetBin(std::string binStr);
    bool save(Bin bin);
    void process(std::string data);
    bool isNumber(std::string s);
private:
    std::string host;
    int port;
    std::string username;
    std::string password;
    std::string db;
    std::string url;
    //std::make_shared<PGPool> pgPool = std::make_shared<PGPool>();
    std::shared_ptr<PGPool> pgPool;
};

#endif /* DBSERVICE_H */

