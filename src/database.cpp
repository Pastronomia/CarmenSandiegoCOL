#include "database.hpp"
#include <iostream>
#include <sqlite3.h>

// Conexión a la base de datos
void Database::conectar() {
    if (sqlite3_open("carmen_sandiego.db", &db)) {
        std::cerr << "No se pudo abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Base de datos abierta correctamente." << std::endl;
    }
}

// Cierre de la base de datos
void Database::cerrar() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;  // Asegurarse de que el puntero esté en null después de cerrar
        std::cout << "Base de datos cerrada correctamente." << std::endl;
    }
}

// Actualizar rango del usuario en la base de datos
void Database::actualizarRango(Usuario& usuario) {
    if (usuario.getCapturas() >= 3) {
        usuario.setRango("Inspector");
    }
    
    const char* sql = "UPDATE Usuarios SET rango = ? WHERE id = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, usuario.getRango().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, usuario.getId());

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Error al actualizar el rango: " << sqlite3_errmsg(db) << std::endl;
        } else {
            std::cout << "Rango actualizado correctamente." << std::endl;
        }
    } else {
        std::cerr << "Error al preparar la actualización: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}
