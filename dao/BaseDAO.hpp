// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#ifndef BASE_DAO_HPP
#define BASE_DAO_HPP

#include <sqlite3.h>
#include <string>
#include <vector>
#include <memory>

class BaseDAO {
public:
    BaseDAO(sqlite3* db);
    virtual ~BaseDAO();

protected:
    sqlite3* db;

    bool ejecutarSQL(const std::string& sql);
    bool prepararStatement(const std::string& sql, sqlite3_stmt** stmt);
    void cerrarStatement(sqlite3_stmt* stmt);
};

#endif // BASE_DAO_HPP


