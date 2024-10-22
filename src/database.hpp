#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sqlite3.h>
#include "Usuario.hpp"

class Database {
public:
    void conectar();
    void cerrar();
    void actualizarRango(Usuario& usuario);
private:
    sqlite3* db;  // Puntero a la base de datos
};

#endif
