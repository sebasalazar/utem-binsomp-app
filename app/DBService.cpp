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

Bin DBService::GetBin(std::string binStr) {
    Bin bin;
    try {
        if (!binStr.empty()) {
            pqxx::nontransaction sql(*(this->connection));
            std::string query = "SELECT pk, bin, brand, issuer, credit FROM bins WHERE bin='" + binStr + "'";
            pqxx::result result = sql.exec(query);
            if (!result.empty()) {
                pqxx::row row = result.at(0);

                long dbid = row.at("pk").as<long>();
                std::string dbbin = row.at("bin").as<std::string>();
                std::string dbbrand = row.at("brand").as<std::string>();
                std::string dbissuer = row.at("issuer").as<std::string>();
                bool dbcredit = row.at("credit").as<bool>();

                bin.SetId(dbid);
                bin.SetBin(dbbin);
                bin.SetBrand(dbbrand);
                bin.SetIssuer(dbissuer);
                bin.SetCredit(dbcredit);

                result.clear();
            }
        }
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }
    return bin;
}

bool DBService::save(Bin bin) {
    bool saved;
    try {
        pqxx::work trx(*(this->connection));
        std::string query;
        if (bin.GetId() == 0) {
            // Nuevo e insertamos
            query = "INSERT INTO bins (bin, brand, issuer, credit) VALUES ('" + trx.esc(bin.GetBin()) + "','" + trx.esc(bin.GetBrand()) + "','" + trx.esc(bin.GetIssuer()) + "','" + trx.esc(std::to_string(bin.IsCredit())) + "')";
        } else {
            // Antiguo y actualizamos
            query = "UPDATE bins SET bin='" + trx.esc(bin.GetBin()) + "', brand='" + trx.esc(bin.GetBrand()) + "', issuer='" + trx.esc(bin.GetIssuer()) + "', credit='" + trx.esc(std::to_string(bin.IsCredit())) + "' WHERE pk='" + trx.esc(std::to_string(bin.GetId())) + "'";
        }

        pqxx::result result = trx.exec(query);
        saved = (!result.empty());
        trx.commit();

    } catch (std::exception const &e) {
        saved = false;
        std::cerr << e.what() << std::endl;
    }
    return saved;
}