// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include "PartidaDAO.hpp"
#include <iostream>

PartidaDAO::PartidaDAO(sqlite3* db) : BaseDAO(db) {}

bool PartidaDAO::crearTabla() {
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS Partida (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            usuario_id INTEGER NOT NULL,
            secuaz_id INTEGER NOT NULL,
            estado TEXT NOT NULL,
            intentos INTEGER NOT NULL DEFAULT 0,
            FOREIGN KEY(usuario_id) REFERENCES Usuario(id),
            FOREIGN KEY(secuaz_id) REFERENCES Secuaz(id)
        );
    )";
    return ejecutarSQL(sql);
}

bool PartidaDAO::insertarPartida(const Partida& partida) {
    std::string sql = "INSERT INTO Partida (usuario_id, secuaz_id, estado, intentos) VALUES (?, ?, ?, ?)";
    sqlite3_stmt* stmt;

    if (!prepararStatement(sql, &stmt)) return false;

    sqlite3_bind_int(stmt, 1, partida.getUsuarioId());
    sqlite3_bind_int(stmt, 2, partida.getSecuazId());
    sqlite3_bind_text(stmt, 3, partida.getEstado().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, partida.getIntentos());

    int rc = sqlite3_step(stmt);
    cerrarStatement(stmt);
    return rc == SQLITE_DONE;
}

bool PartidaDAO::actualizarPartida(const Partida& partida) {
    std::string sql = "UPDATE Partida SET estado = ?, intentos = ? WHERE id = ?";
    sqlite3_stmt* stmt;

    if (!prepararStatement(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, partida.getEstado().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, partida.getIntentos());
    sqlite3_bind_int(stmt, 3, partida.getId());

    int rc = sqlite3_step(stmt);
    cerrarStatement(stmt);
    return rc == SQLITE_DONE;
}

bool PartidaDAO::eliminarPartida(int id) {
    std::string sql = "DELETE FROM Partida WHERE id = ?";
    sqlite3_stmt* stmt;

    if (!prepararStatement(sql, &stmt)) return false;

    sqlite3_bind_int(stmt, 1, id);

    int rc = sqlite3_step(stmt);
    cerrarStatement(stmt);
    return rc == SQLITE_DONE;
}

std::shared_ptr<Partida> PartidaDAO::obtenerPartidaPorId(int id) {
    std::string sql = "SELECT * FROM Partida WHERE id = ?";
    sqlite3_stmt* stmt;
    std::shared_ptr<Partida> partida = nullptr;

    if (!prepararStatement(sql, &stmt)) return partida;

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        partida = std::make_shared<Partida>(
            sqlite3_column_int(stmt, 0),
            sqlite3_column_int(stmt, 1),
            sqlite3_column_int(stmt, 2),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            sqlite3_column_int(stmt, 4)
        );
    }

    cerrarStatement(stmt);
    return partida;
}

std::vector<Partida> PartidaDAO::obtenerTodasLasPartidas() {
    std::string sql = "SELECT * FROM Partida";
    sqlite3_stmt* stmt;
    std::vector<Partida> partidas;

    if (!prepararStatement(sql, &stmt)) return partidas;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Partida partida(
            sqlite3_column_int(stmt, 0),
            sqlite3_column_int(stmt, 1),
            sqlite3_column_int(stmt, 2),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            sqlite3_column_int(stmt, 4)
        );
        partidas.push_back(partida);
    }

    cerrarStatement(stmt);
    return partidas;
}

