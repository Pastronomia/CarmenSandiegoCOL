#include <string>
// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include "UsuarioDAO.hpp"
#include <iostream>

// Constructor: hereda de BaseDAO
UsuarioDAO::UsuarioDAO(sqlite3* db) : BaseDAO(db) {}

// Función auxiliar para ejecutar consultas con sqlite3
bool UsuarioDAO::ejecutarConsulta(const std::string& sql, sqlite3_stmt** stmt) {
    if (!prepararStatement(sql, stmt)) return false;
    int rc = sqlite3_step(*stmt);
    cerrarStatement(*stmt);
    return rc == SQLITE_DONE;
}

// Crear tabla de usuarios en la base de datos
bool UsuarioDAO::crearTabla() {
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS Usuario (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nombre TEXT NOT NULL,
            apellido TEXT NOT NULL,
            contrasena TEXT NOT NULL,
            rango TEXT NOT NULL,
            capturas INTEGER DEFAULT 0,
            progreso TEXT
        );
    )";
    return ejecutarSQL(sql);
}

// Función auxiliar para ligar los valores de un usuario a una sentencia SQL
void UsuarioDAO::ligarValoresUsuario(sqlite3_stmt* stmt, const Usuario& usuario, bool incluirId) {
    sqlite3_bind_text(stmt, 1, usuario.getNombre().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, usuario.getApellido().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, usuario.getContrasena().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, usuario.getRango().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, usuario.getCapturas());
    sqlite3_bind_text(stmt, 6, usuario.getProgreso().c_str(), -1, SQLITE_STATIC);

    if (incluirId) {
        sqlite3_bind_int(stmt, 7, usuario.getId());
    }
}

// Insertar un nuevo usuario en la base de datos
bool UsuarioDAO::insertarUsuario(const Usuario& usuario) {
    std::string sql = "INSERT INTO Usuario (nombre, apellido, contrasena, rango, capturas, progreso) VALUES (?, ?, ?, ?, ?, ?)";
    sqlite3_stmt* stmt;

    if (!prepararStatement(sql, &stmt)) return false;

    ligarValoresUsuario(stmt, usuario);
    return ejecutarConsulta(sql, &stmt);
}

// Actualizar un usuario existente en la base de datos
bool UsuarioDAO::actualizarUsuario(const Usuario& usuario) {
    std::string sql = "UPDATE Usuario SET nombre = ?, apellido = ?, contrasena = ?, rango = ?, capturas = ?, progreso = ? WHERE id = ?";
    sqlite3_stmt* stmt;

    if (!prepararStatement(sql, &stmt)) return false;

    ligarValoresUsuario(stmt, usuario, true);
    return ejecutarConsulta(sql, &stmt);
}

// Eliminar un usuario de la base de datos por su ID
bool UsuarioDAO::eliminarUsuario(int id) {
    std::string sql = "DELETE FROM Usuario WHERE id = ?";
    sqlite3_stmt* stmt;

    if (!prepararStatement(sql, &stmt)) return false;

    sqlite3_bind_int(stmt, 1, id);
    return ejecutarConsulta(sql, &stmt);
}

// Obtener un usuario por su ID
std::shared_ptr<Usuario> UsuarioDAO::obtenerUsuarioPorId(int id) {
    std::string sql = "SELECT * FROM Usuario WHERE id = ?";
    sqlite3_stmt* stmt;
    std::shared_ptr<Usuario> usuario = nullptr;

    if (!prepararStatement(sql, &stmt)) return usuario;

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        usuario = std::make_shared<Usuario>(
            sqlite3_column_int(stmt, 0),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)),
            sqlite3_column_int(stmt, 5),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6))
        );
    }

    cerrarStatement(stmt);
    return usuario;
}

// Obtener un usuario por su nombre
std::shared_ptr<Usuario> UsuarioDAO::obtenerUsuarioPorNombre(const std::string& nombre) {
    std::string sql = "SELECT * FROM Usuario WHERE nombre = ?";
    sqlite3_stmt* stmt;
    std::shared_ptr<Usuario> usuario = nullptr;

    if (!prepararStatement(sql, &stmt)) return usuario;

    sqlite3_bind_text(stmt, 1, nombre.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        usuario = std::make_shared<Usuario>(
            sqlite3_column_int(stmt, 0),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)),
            sqlite3_column_int(stmt, 5),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6))
        );
    }

    cerrarStatement(stmt);
    return usuario;
}

// Obtener todos los usuarios de la base de datos
std::vector<Usuario> UsuarioDAO::obtenerTodosLosUsuarios() {
    std::string sql = "SELECT * FROM Usuario";
    sqlite3_stmt* stmt;
    std::vector<Usuario> usuarios;

    if (!prepararStatement(sql, &stmt)) return usuarios;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Usuario usuario(
            sqlite3_column_int(stmt, 0),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)),
            sqlite3_column_int(stmt, 5),
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6))
        );
        usuarios.push_back(usuario);
    }

    cerrarStatement(stmt);
    return usuarios;
}

// Insertar usuarios iniciales (opcional)
bool UsuarioDAO::insertarUsuariosIniciales() {
    // Implementa lógica para insertar datos iniciales si es necesario
    return true;
}

