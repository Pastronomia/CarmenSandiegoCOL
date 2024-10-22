#include "PistaDAO.hpp"
#include <random>
#include <memory>
#include "Pista.hpp"

PistaDAO::PistaDAO(sqlite3* db) : BaseDAO(db) {}

bool PistaDAO::crearTabla() {
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS Pista (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            localidad_id INTEGER NOT NULL,
            numero INTEGER NOT NULL,
            descripcion TEXT NOT NULL,
            correcta BOOLEAN NOT NULL,
            FOREIGN KEY(localidad_id) REFERENCES Localidad(id)
        );
    )";
    return ejecutarSQL(sql);
}

bool PistaDAO::insertarPista(const Pista& pista) {
    std::string sql = "INSERT INTO Pista (localidad_id, numero, descripcion, correcta) VALUES (?, ?, ?, ?)";
    sqlite3_stmt* stmt;

    if (!prepararStatement(sql, &stmt)) return false;

    sqlite3_bind_int(stmt, 1, pista.getLocalidadId());
    sqlite3_bind_int(stmt, 2, pista.getNumero());
    sqlite3_bind_text(stmt, 3, pista.getDescripcion().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, pista.esCorrecta() ? 1 : 0);

    int rc = sqlite3_step(stmt);
    cerrarStatement(stmt);
    return rc == SQLITE_DONE;
}

bool PistaDAO::actualizarPista(const Pista& pista) {
    std::string sql = "UPDATE Pista SET localidad_id = ?, numero = ?, descripcion = ?, correcta = ? WHERE id = ?";
    sqlite3_stmt* stmt;

    if (!prepararStatement(sql, &stmt)) return false;

    sqlite3_bind_int(stmt, 1, pista.getLocalidadId());
    sqlite3_bind_int(stmt, 2, pista.getNumero());
    sqlite3_bind_text(stmt, 3, pista.getDescripcion().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, pista.esCorrecta() ? 1 : 0);
    sqlite3_bind_int(stmt, 5, pista.getId());

    int rc = sqlite3_step(stmt);
    cerrarStatement(stmt);
    return rc == SQLITE_DONE;
}

bool PistaDAO::eliminarPista(int id) {
    std::string sql = "DELETE FROM Pista WHERE id = ?";
    sqlite3_stmt* stmt;

    if (!prepararStatement(sql, &stmt)) return false;

    sqlite3_bind_int(stmt, 1, id);

    int rc = sqlite3_step(stmt);
    cerrarStatement(stmt);
    return rc == SQLITE_DONE;
}

std::shared_ptr<Pista> PistaDAO::obtenerPistaPorId(int id) {
    std::string sql = "SELECT * FROM Pista WHERE id = ?";
    sqlite3_stmt* stmt;
    std::shared_ptr<Pista> pista = nullptr;

    if (!prepararStatement(sql, &stmt)) return pista;

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        pista = std::make_shared<Pista>(
            sqlite3_column_int(stmt, 0),
            sqlite3_column_int(stmt, 1),
            sqlite3_column_int(stmt, 2),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            sqlite3_column_int(stmt, 4) == 1
        );
    }

    cerrarStatement(stmt);
    return pista;
}

std::vector<Pista> PistaDAO::obtenerPistasPorLocalidad(int localidadId) {
    std::string sql = "SELECT * FROM Pista WHERE localidad_id = ?";
    sqlite3_stmt* stmt;
    std::vector<Pista> pistas;

    if (!prepararStatement(sql, &stmt)) return pistas;

    sqlite3_bind_int(stmt, 1, localidadId);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Pista pista(
            sqlite3_column_int(stmt, 0),
            sqlite3_column_int(stmt, 1),
            sqlite3_column_int(stmt, 2),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            sqlite3_column_int(stmt, 4) == 1
        );
        pistas.push_back(pista);
    }

    cerrarStatement(stmt);
    return pistas;
}

std::vector<Pista> PistaDAO::obtenerPistasAleatoriasPorLocalidad(int localidadId, int cantidad) {
    auto pistas = obtenerPistasPorLocalidad(localidadId);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pistas.begin(), pistas.end(), g);

    if (pistas.size() > cantidad) {
        pistas.resize(cantidad);
    }
    return pistas;
}
