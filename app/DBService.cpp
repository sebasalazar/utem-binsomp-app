#include <omp.h>

#include "DBService.h"

DBService::DBService() {
    this->host = "127.0.0.1";
    this->port = 5432;
    this->db = "cpyddb";
    this->username = "cpyd";
    this->password = "cpyd";

    this->url = "host='" + this->host + "' port='" + std::to_string(this->port) + "' dbname='" + this->db + "' user='" + this->username + "' password='" + this->password + "' client_encoding='UTF8'";
    //    this->connection = new pqxx::connection(url);
    pgPool = std::make_shared<PGPool>(url);
}

DBService::DBService(std::string host, int port, std::string username, std::string password, std::string db) {
    this->host = host;
    this->port = port;
    this->db = db;
    this->username = username;
    this->password = password;

    this->url = "host='" + this->host + "' port='" + std::to_string(this->port) + "' dbname='" + this->db + "' user='" + this->username + "' password='" + this->password + "'";
    //    this->connection = new pqxx::connection(url);
    pgPool = std::make_shared<PGPool>(url);
}

DBService::~DBService() {
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

std::string DBService::GetVersion() const {
    std::shared_ptr<pqxx::lazyconnection> connection = pgPool->connection();
    pqxx::nontransaction sql(reinterpret_cast<pqxx::lazyconnection&> (*connection.get()));
    std::string query = "SELECT VERSION()";
    pqxx::result result = sql.exec(query);
    pqxx::row row = result.at(0);

    std::string version = row.at("version").as<std::string>();
    result.clear();

    pgPool->freeConnection(connection);
    return version;
}

Bin DBService::GetBin(std::string binStr) {
    Bin bin;
    try {
        if (!binStr.empty()) {
            std::shared_ptr<pqxx::lazyconnection> connection = pgPool->connection();

            pqxx::nontransaction sql(reinterpret_cast<pqxx::lazyconnection&> (*connection.get()));
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

                pgPool->freeConnection(connection);
            }
        }
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }
    return bin;
}

bool DBService::save(Bin bin) {
    bool saved = false;
    try {
        if (isNumber(bin.GetBin())) {
            std::shared_ptr<pqxx::lazyconnection> connection = pgPool->connection();

            pqxx::work trx(reinterpret_cast<pqxx::lazyconnection&> (*connection.get()));
            std::string query;
            if (bin.GetId() == 0) {
                // Nuevo e insertamos
                query = "INSERT INTO bins (bin, brand, issuer, credit) VALUES ('" + trx.esc(bin.GetBin()) + "','" + trx.esc(bin.GetBrand()) + "','" + trx.esc(bin.GetIssuer()) + "','" + trx.esc(std::to_string(bin.IsCredit())) + "')";
            } else {
                // Antiguo y actualizamos
                query = "UPDATE bins SET bin='" + trx.esc(bin.GetBin()) + "', brand='" + trx.esc(bin.GetBrand()) + "', issuer='" + trx.esc(bin.GetIssuer()) + "', credit='" + trx.esc(std::to_string(bin.IsCredit())) + "' WHERE pk='" + trx.esc(std::to_string(bin.GetId())) + "'";
            }

            trx.exec(query);
            trx.commit();

            pgPool->freeConnection(connection);

            saved = true;
        }
    } catch (std::exception const &e) {
        saved = false;
        std::cerr << e.what() << std::endl;
    }
    return saved;
}

void DBService::process(std::string data) {
    Bin bin;

    data.erase(std::remove(data.begin(), data.end(), '\"'), data.end());
    std::stringstream ss(data);

    std::string text;
    int column = 0;
    while (std::getline(ss, text, ';')) {
        switch (column) {

            case 0:
                bin.SetBin(text);
                break;

            case 1:
                bin.SetBrand(text);
                break;

            case 2:
                bin.SetIssuer(text);
                break;

            case 3:
                if (text == "t") {
                    bin.SetCredit(true);
                } else {
                    bin.SetCredit(false);
                }
                break;
        }

        column += 1;
    }

    // Bin completo
    // std::cout << bin.to_string() << std::endl;

    bool ok = false;
    Bin dbBin = this->GetBin(bin.GetBin());
    if (dbBin.GetBin().empty()) {
        ok = this->save(bin);
    }

    if (ok) {
        std::cout << ".";
    }
}

bool DBService::isNumber(std::string text) {
    std::string::const_iterator it = text.begin();
    while (it != text.end() && std::isdigit(*it)) ++it;
    return !text.empty() && it == text.end();
}