#include "BaseDAO.hpp"
// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include "database_initialization.hpp"
#include <sqlite3.h>
#include "UsuarioDAO.hpp"
#include "LocalidadDAO.hpp"
#include "PistaDAO.hpp"
#include "SecuazDAO.hpp"
#include <iostream>
#include <memory>

bool DatabaseInitialization::insertarDatosIniciales(sqlite3* db) {

    UsuarioDAO usuarioDAO(db);
    LocalidadDAO localidadDAO(db);
    PistaDAO pistaDAO(db);
    SecuazDAO secuazDAO(db, std::make_shared<LocalidadDAO>(db));


    // Insertar usuarios iniciales
    // Verifica si ya existe un usuario con el nombre "Carmen" para evitar duplicados
    if (!usuarioDAO.obtenerUsuarioPorNombre("Carmen")) {
        usuarioDAO.insertarUsuario(Usuario(0, "Carmen", "Sandiego", "password", "Mastermind", 0, ""));
    } else {
        std::cout << "Usuario 'Carmen Sandiego' ya existe, se omite la inserción." << std::endl;
    }

    // Insertar localidades iniciales
    auto colonia = std::make_shared<Localidad>(Localidad(0, "Colonia", "Descripción de Colonia", -34.471, -57.844));
    if (!localidadDAO.obtenerLocalidadPorId(0)) {
        localidadDAO.insertarLocalidad(*colonia);
    } else {
        std::cout << "Localidad 'Colonia' ya existe, se omite la inserción." << std::endl;
    }

    if (!localidadDAO.obtenerLocalidadPorId(1)) {
        localidadDAO.insertarLocalidad(Localidad(1, "Montevideo", "Descripción de Montevideo", -34.9011, -56.1645));
    } else {
        std::cout << "Localidad 'Montevideo' ya existe, se omite la inserción." << std::endl;
    }

    // Insertar pistas iniciales
    if (!pistaDAO.obtenerPistaPorId(0)) {
        pistaDAO.insertarPista(Pista(0, 0, 1, "Una pista importante.", true));
    } else {
        std::cout << "Pista con ID 0 ya existe, se omite la inserción." << std::endl;
    }

    if (!pistaDAO.obtenerPistaPorId(1)) {
        pistaDAO.insertarPista(Pista(1, 1, 2, "Otra pista relevante.", false));
    } else {
        std::cout << "Pista con ID 1 ya existe, se omite la inserción." << std::endl;
    }

    // Insertar secuaces iniciales
    if (!secuazDAO.obtenerSecuazPorId(0)) {
        secuazDAO.insertarSecuaz(Secuaz(0, "Villano", "Hacker", 10, colonia, false));
    } else {
        std::cout << "Secuaz con ID 0 ya existe, se omite la inserción." << std::endl;
    }

    return true;
}

