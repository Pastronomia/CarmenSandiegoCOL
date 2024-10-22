#include <string>
// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include "LocalidadDAO.hpp"
#include <iostream>

LocalidadDAO::LocalidadDAO(sqlite3* db) : BaseDAO(db) {}

bool LocalidadDAO::crearTabla() {
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS Localidad (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nombre TEXT NOT NULL UNIQUE,
            descripcion TEXT,
            latitud REAL,
            longitud REAL
        );
    )";
    return ejecutarSQL(sql);
}

bool LocalidadDAO::insertarLocalidad(const Localidad& localidad) {
    std::string sql = "INSERT INTO Localidad (nombre, descripcion, latitud, longitud) VALUES (?, ?, ?, ?)";
    sqlite3_stmt* stmt;

    if (!prepararStatement(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, localidad.getNombre().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, localidad.getDescripcion().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, localidad.getLatitud());
    sqlite3_bind_double(stmt, 4, localidad.getLongitud());

    int rc = sqlite3_step(stmt);
    cerrarStatement(stmt);
    return rc == SQLITE_DONE;
}

bool LocalidadDAO::actualizarLocalidad(const Localidad& localidad) {
    std::string sql = "UPDATE Localidad SET nombre = ?, descripcion = ?, latitud = ?, longitud = ? WHERE id = ?";
    sqlite3_stmt* stmt;

    if (!prepararStatement(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, localidad.getNombre().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, localidad.getDescripcion().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, localidad.getLatitud());
    sqlite3_bind_double(stmt, 4, localidad.getLongitud());
    sqlite3_bind_int(stmt, 5, localidad.getId());

    int rc = sqlite3_step(stmt);
    cerrarStatement(stmt);
    return rc == SQLITE_DONE;
}

bool LocalidadDAO::eliminarLocalidad(int id) {
    std::string sql = "DELETE FROM Localidad WHERE id = ?";
    sqlite3_stmt* stmt;

    if (!prepararStatement(sql, &stmt)) return false;

    sqlite3_bind_int(stmt, 1, id);

    int rc = sqlite3_step(stmt);
    cerrarStatement(stmt);
    return rc == SQLITE_DONE;
}

std::shared_ptr<Localidad> LocalidadDAO::obtenerLocalidadPorId(int id) {
    std::string sql = "SELECT * FROM Localidad WHERE id = ?";
    sqlite3_stmt* stmt;
    std::shared_ptr<Localidad> localidad = nullptr;

    if (!prepararStatement(sql, &stmt)) return localidad;

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        localidad = std::make_shared<Localidad>(
            sqlite3_column_int(stmt, 0),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            sqlite3_column_double(stmt, 3),
            sqlite3_column_double(stmt, 4)
        );
    }

    cerrarStatement(stmt);
    return localidad;
}

std::vector<Localidad> LocalidadDAO::obtenerTodasLasLocalidades() {
    std::string sql = "SELECT * FROM Localidad";
    sqlite3_stmt* stmt;
    std::vector<Localidad> localidades;

    if (!prepararStatement(sql, &stmt)) return localidades;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Localidad localidad(
            sqlite3_column_int(stmt, 0),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            sqlite3_column_double(stmt, 3),
            sqlite3_column_double(stmt, 4)
        );
        localidades.push_back(localidad);
    }

    cerrarStatement(stmt);
    return localidades;
}

