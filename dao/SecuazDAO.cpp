// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include "LocalidadDAO.hpp"
#include <gtkmm.h>
#include "SecuazDAO.hpp"
#include "Secuaz.hpp"
#include "LocalidadDAO.hpp"
#include <sqlite3.h>
#include <iostream>
#include <functional>

// Constructor de SecuazDAO
SecuazDAO::SecuazDAO(sqlite3* db, std::shared_ptr<LocalidadDAO> localidadDAO)
    : BaseDAO(db), localidadDAO(localidadDAO) {}

// Función auxiliar para ejecutar declaraciones SQL
bool SecuazDAO::ejecutarDeclaracion(const char* sql, std::function<void(sqlite3_stmt*)> bindFn) {
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparando la declaración: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    if (bindFn) {
        bindFn(stmt);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error ejecutando la declaración: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

// Crear tabla Secuaz
bool SecuazDAO::crearTabla() {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS Secuaz (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nombre TEXT NOT NULL,
            habilidad TEXT,
            peligrosidad INTEGER,
            localidad_id INTEGER,
            capturado INTEGER DEFAULT 0,
            FOREIGN KEY(localidad_id) REFERENCES Localidad(id)
        );
    )";
    return ejecutarDeclaracion(sql);
}

// Insertar un Secuaz
bool SecuazDAO::insertarSecuaz(const Secuaz& secuaz) {
    const char* sql = "INSERT INTO Secuaz (nombre, habilidad, peligrosidad, localidad_id, capturado) VALUES (?, ?, ?, ?, ?);";
    return ejecutarDeclaracion(sql, [&secuaz](sqlite3_stmt* stmt) {
        sqlite3_bind_text(stmt, 1, secuaz.getNombre().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, secuaz.getHabilidad().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, secuaz.getPeligrosidad());
        sqlite3_bind_int(stmt, 4, secuaz.getLocalidad()->getId());
        sqlite3_bind_int(stmt, 5, secuaz.isCapturado() ? 1 : 0);
    });
}

// Actualizar un Secuaz
bool SecuazDAO::actualizarSecuaz(const Secuaz& secuaz) {
    const char* sql = "UPDATE Secuaz SET nombre = ?, habilidad = ?, peligrosidad = ?, localidad_id = ?, capturado = ? WHERE id = ?;";
    return ejecutarDeclaracion(sql, [&secuaz](sqlite3_stmt* stmt) {
        sqlite3_bind_text(stmt, 1, secuaz.getNombre().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, secuaz.getHabilidad().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, secuaz.getPeligrosidad());
        sqlite3_bind_int(stmt, 4, secuaz.getLocalidad()->getId());
        sqlite3_bind_int(stmt, 5, secuaz.isCapturado() ? 1 : 0);
        sqlite3_bind_int(stmt, 6, secuaz.getId());
    });
}

// Eliminar un Secuaz
bool SecuazDAO::eliminarSecuaz(int id) {
    const char* sql = "DELETE FROM Secuaz WHERE id = ?;";
    return ejecutarDeclaracion(sql, [id](sqlite3_stmt* stmt) {
        sqlite3_bind_int(stmt, 1, id);
    });
}

// Obtener un Secuaz por ID
std::shared_ptr<Secuaz> SecuazDAO::obtenerSecuazPorId(int id) {
    const char* sql = "SELECT id, nombre, habilidad, peligrosidad, localidad_id, capturado FROM Secuaz WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparando la declaración: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }

    sqlite3_bind_int(stmt, 1, id);

    std::shared_ptr<Secuaz> secuaz = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        secuaz = std::make_shared<Secuaz>(
            sqlite3_column_int(stmt, 0),  // ID
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),  // Nombre
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),  // Habilidad
            sqlite3_column_int(stmt, 3),  // Peligrosidad
            localidadDAO->obtenerLocalidadPorId(sqlite3_column_int(stmt, 4)),  // Localidad
            sqlite3_column_int(stmt, 5) != 0  // Capturado (convertir a booleano)
        );
    }

    sqlite3_finalize(stmt);
    return secuaz;
}

// Obtener todos los Secuaces no capturados
std::vector<Secuaz> SecuazDAO::obtenerSecuacesNoCapturados() {
    const char* sql = "SELECT id, nombre, habilidad, peligrosidad, localidad_id, capturado FROM Secuaz WHERE capturado = 0;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparando la declaración: " << sqlite3_errmsg(db) << std::endl;
        return {};
    }

    std::vector<Secuaz> secuaces;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        secuaces.emplace_back(
            sqlite3_column_int(stmt, 0),  // ID
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),  // Nombre
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),  // Habilidad
            sqlite3_column_int(stmt, 3),  // Peligrosidad
            localidadDAO->obtenerLocalidadPorId(sqlite3_column_int(stmt, 4)),  // Localidad
            sqlite3_column_int(stmt, 5) != 0  // Capturado (convertir a booleano)
        );
    }

    sqlite3_finalize(stmt);
    return secuaces;
}

