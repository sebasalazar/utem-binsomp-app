#include "DBService.h"

DBService::DBService() {
    this->host = "157.245.230.38";
    this->port = 6432;
    this->db = "cpyddb";
    this->username = "cpyd";
    this->password = "cpyd";

    const std::string url = "host='" + this->host + "' port='" + std::to_string(this->port) + "' dbname='" + this->db + "' user='" + this->username + "' password='" + this->password + "'";
    this->connection = new pqxx::connection(url);
}

DBService::DBService(std::string host, int port, std::string username, std::string password, std::string db) {
    this->host = host;
    this->port = port;
    this->db = db;
    this->username = username;
    this->password = password;

    const std::string url = "host='" + this->host + "' port='" + std::to_string(this->port) + "' dbname='" + this->db + "' user='" + this->username + "' password='" + this->password + "'";
    this->connection = new pqxx::connection(url);
}

DBService::~DBService() {
    try {
        this->connection->disconnect();
        delete this->connection;
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }
}

std::string DBService::GetDb() const {
    return db;
}

void DBService::SetDb(std::string db) {
    this->db = db;
}

std::string DBService::GetHost() const {
    return host;
}

void DBService::SetHost(std::string host) {
    this->host = host;
}

std::string DBService::GetPassword() const {
    return password;
}

void DBService::SetPassword(std::string password) {
    this->password = password;
}

int DBService::GetPort() const {
    return port;
}

void DBService::SetPort(int port) {
    this->port = port;
}

std::string DBService::GetUsername() const {
    return username;
}

void DBService::SetUsername(std::string username) {
    this->username = username;
}

pqxx::connection* DBService::GetConnection() const {
    return connection;
}

std::string DBService::GetVersion() const {
    pqxx::nontransaction sql(*(this->connection));
    std::string query = "SELECT VERSION()";
    pqxx::result result = sql.exec(query);
    pqxx::row row = result.at(0);

    std::string version = row.at("version").as<std::string>();
    result.clear();

    return version;
}