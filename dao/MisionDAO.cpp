#include <string>
// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include "MisionDAO.hpp"
#include <iostream>

MisionDAO::MisionDAO(sqlite3* db) : BaseDAO(db) {}

bool MisionDAO::crearTabla() {
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS Mision (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            titulo TEXT NOT NULL UNIQUE,
            descripcion TEXT,
            objetivo TEXT NOT NULL,
            completada BOOLEAN NOT NULL DEFAULT FALSE
        );
    )";
    return ejecutarSQL(sql);
}

bool MisionDAO::insertarMision(const Mision& mision) {
    std::string sql = "INSERT INTO Mision (titulo, descripcion, objetivo, completada) VALUES (?, ?, ?, ?)";
    sqlite3_stmt* stmt;

    if (!prepararStatement(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, mision.getTitulo().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, mision.getDescripcion().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, mision.getObjetivo().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, mision.isCompletada() ? 1 : 0);

    int rc = sqlite3_step(stmt);
    cerrarStatement(stmt);
    return rc == SQLITE_DONE;
}

bool MisionDAO::actualizarMision(const Mision& mision) {
    std::string sql = "UPDATE Mision SET titulo = ?, descripcion = ?, objetivo = ?, completada = ? WHERE id = ?";
    sqlite3_stmt* stmt;

    if (!prepararStatement(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, mision.getTitulo().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, mision.getDescripcion().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, mision.getObjetivo().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, mision.isCompletada() ? 1 : 0);
    sqlite3_bind_int(stmt, 5, mision.getId());

    int rc = sqlite3_step(stmt);
    cerrarStatement(stmt);
    return rc == SQLITE_DONE;
}

bool MisionDAO::eliminarMision(int id) {
    std::string sql = "DELETE FROM Mision WHERE id = ?";
    sqlite3_stmt* stmt;

    if (!prepararStatement(sql, &stmt)) return false;

    sqlite3_bind_int(stmt, 1, id);

    int rc = sqlite3_step(stmt);
    cerrarStatement(stmt);
    return rc == SQLITE_DONE;
}

std::shared_ptr<Mision> MisionDAO::obtenerMisionPorId(int id) {
    std::string sql = "SELECT * FROM Mision WHERE id = ?";
    sqlite3_stmt* stmt;
    std::shared_ptr<Mision> mision = nullptr;

    if (!prepararStatement(sql, &stmt)) return mision;

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        mision = std::make_shared<Mision>(
            sqlite3_column_int(stmt, 0),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            sqlite3_column_int(stmt, 4) == 1
        );
    }

    cerrarStatement(stmt);
    return mision;
}

std::vector<Mision> MisionDAO::obtenerTodasLasMisiones() {
    std::string sql = "SELECT * FROM Mision";
    sqlite3_stmt* stmt;
    std::vector<Mision> misiones;

    if (!prepararStatement(sql, &stmt)) return misiones;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Mision mision(
            sqlite3_column_int(stmt, 0),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            sqlite3_column_int(stmt, 4) == 1
        );
        misiones.push_back(mision);
    }

    cerrarStatement(stmt);
    return misiones;
}

