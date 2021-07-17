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
    /**
     * Constructor vacío, que usa los valores por defecto.
     */
    DBService();
    /**
     * 
     * @param host Host/Dominio del servidor
     * @param port Puerto del servidor
     * @param username Nombre de usuario
     * @param password Contraseña
     * @param db El nombre de la base de datos
     */
    DBService(std::string host, int port, std::string username, std::string password, std::string db);
    /**
     * Destructor
     */
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
    /**
     * 
     * @return Devuelve la versión del motor de base de datos.
     */
    std::string GetVersion() const;
    /**
     * 
     * @param binStr Números del Bin.
     * @return El objeto mapeado
     */
    Bin GetBin(std::string binStr);
    /**
     * 
     * @param bin Objeto
     * @return el objeto que fue persistido en la base de datos.
     */
    bool save(Bin bin);
    void process(std::string data);
    /**
     * 
     * @param s Cadena de texto
     * @return true si a la cadena de texto sólo está compuesta por digitos o false en cualquier otro caso.
     */
    bool isNumber(std::string s);
private:
    /**
     * Host de conexión
     */
    std::string host;
    /**
     * Puerto de conexión
     */
    int port;
    /**
     * Usuario de conexión
     */
    std::string username;
    /**
     * Contraseña
     */
    std::string password;
    /**
     * Nombre de la base de datos.
     */
    std::string db;
    /**
     * URL de conexión
     */
    std::string url;

    /**
     * Pool de conexión
     */
    std::shared_ptr<PGPool> pgPool;
};

#endif /* DBSERVICE_H */

