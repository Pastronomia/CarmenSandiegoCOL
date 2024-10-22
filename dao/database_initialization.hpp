// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#ifndef DATABASE_INITIALIZATION_HPP
#define DATABASE_INITIALIZATION_HPP

#include <string>
#include <sqlite3.h>

class DatabaseInitialization {
public:
    static bool inicializarBaseDeDatos(const std::string& rutaDB);

private:
    static bool crearTablas(sqlite3* db);
    static bool insertarDatosIniciales(sqlite3* db);
};

#endif // DATABASE_INITIALIZATION_HPP

