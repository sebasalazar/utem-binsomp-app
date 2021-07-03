#ifndef DBSERVICE_H
#define DBSERVICE_H

#include <iostream>
#include <string>
#include <algorithm>
#include <pqxx/pqxx>

#include "Bin.h"

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
    pqxx::connection* GetConnection() const;

    /// Consultas
    std::string GetVersion() const;
    Bin GetBin(std::string binStr);
    bool save(Bin bin);
private:
    std::string host;
    int port;
    std::string username;
    std::string password;
    std::string db;
    pqxx::connection *connection;
};

#endif /* DBSERVICE_H */

