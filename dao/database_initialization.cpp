// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include "database_initialization.hpp"
#include "UsuarioDAO.hpp"
#include "LocalidadDAO.hpp"
#include "PistaDAO.hpp"
#include "SecuazDAO.hpp"
#include <iostream>
#include <sqlite3.h>

// Función para leer secuaces desde la base de datos
void leerSecuaces(sqlite3* db) {
    const char* sql = "SELECT id, nombre, habilidad, peligrosidad, localidad_id, capturado FROM Secuaz";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        std::cout << "ID | Nombre | Habilidad | Peligrosidad | Localidad ID | Capturado\n";
        std::cout << "---------------------------------------------------------------\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* nombre = sqlite3_column_text(stmt, 1);
            const unsigned char* habilidad = sqlite3_column_text(stmt, 2);
            int peligrosidad = sqlite3_column_int(stmt, 3);
            int localidad_id = sqlite3_column_int(stmt, 4);
            int capturado = sqlite3_column_int(stmt, 5);

            std::cout << id << " | " << nombre << " | " << habilidad << " | " << peligrosidad << " | " << localidad_id << " | " << (capturado ? "Sí" : "No") << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Error al preparar la consulta: " << sqlite3_errmsg(db) << std::endl;
    }
}

bool DatabaseInitialization::insertarDatosIniciales(sqlite3* db) {
    UsuarioDAO usuarioDAO(db);
    LocalidadDAO localidadDAO(db);
    PistaDAO pistaDAO(db);
    SecuazDAO secuazDAO(db, std::make_shared<LocalidadDAO>(db));

    // Insertar usuarios iniciales
    usuarioDAO.insertarUsuario(Usuario(0, "Carmen", "Sandiego", "password", "Mastermind", 0, ""));

    // Insertar localidades iniciales
    auto colonia = std::make_shared<Localidad>(Localidad(0, "Colonia", "Descripción de Colonia", -34.471, -57.844));
    localidadDAO.insertarLocalidad(*colonia);
    localidadDAO.insertarLocalidad(Localidad(1, "Montevideo", "Descripción de Montevideo", -34.9011, -56.1645));

    // Insertar pistas iniciales
    pistaDAO.insertarPista(Pista(0, 0, 1, "Una pista importante.", true));
    pistaDAO.insertarPista(Pista(1, 1, 2, "Otra pista relevante.", false));

    // Leer secuaces de la base de datos y mostrarlos
    leerSecuaces(db);

    return true;
}

bool DatabaseInitialization::crearTablas(sqlite3* db) {
    const char* sqlUsuario = R"(
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

    const char* sqlLocalidad = R"(
        CREATE TABLE IF NOT EXISTS Localidad (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nombre TEXT NOT NULL UNIQUE,
            descripcion TEXT,
            latitud REAL,
            longitud REAL
        );
    )";

    const char* sqlPista = R"(
        CREATE TABLE IF NOT EXISTS Pista (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            localidad_id INTEGER NOT NULL,
            numero INTEGER NOT NULL,
            descripcion TEXT NOT NULL,
            correcta BOOLEAN NOT NULL,
            FOREIGN KEY(localidad_id) REFERENCES Localidad(id)
        );
    )";

    const char* sqlSecuaz = R"(
        CREATE TABLE IF NOT EXISTS Secuaz (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nombre TEXT NOT NULL,
            habilidad TEXT NOT NULL,
            peligrosidad INTEGER NOT NULL,
            localidad_id INTEGER,
            capturado BOOLEAN DEFAULT FALSE,
            FOREIGN KEY(localidad_id) REFERENCES Localidad(id)
        );
    )";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, sqlUsuario, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error creando tabla Usuario: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    if (sqlite3_exec(db, sqlLocalidad, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error creando tabla Localidad: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    if (sqlite3_exec(db, sqlPista, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error creando tabla Pista: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    if (sqlite3_exec(db, sqlSecuaz, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Error creando tabla Secuaz: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

bool DatabaseInitialization::inicializarBaseDeDatos(const std::string& rutaDB) {
    sqlite3* db;
    int rc = sqlite3_open(rutaDB.c_str(), &db);

    if (rc) {
        std::cerr << "No se pudo abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    if (!crearTablas(db)) {
        std::cerr << "Error creando tablas." << std::endl;
        sqlite3_close(db);
        return false;
    }

    if (!insertarDatosIniciales(db)) {
        std::cerr << "Error insertando datos iniciales." << std::endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);
    return true;
}

