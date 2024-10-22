#include <string>
// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include "Usuario.hpp"

// Constructor
Usuario::Usuario(int id, const std::string& nombre, const std::string& apellido, const std::string& contrasena, const std::string& rango, int capturas, const std::string& progreso)
    : id(id), nombre(nombre), apellido(apellido), contrasena(contrasena), rango(rango), capturas(capturas), progreso(progreso) {}

// Getters
int Usuario::getId() const {
    return id;
}

std::string Usuario::getNombre() const {
    return nombre;
}

std::string Usuario::getApellido() const {
    return apellido;
}

std::string Usuario::getContrasena() const {
    return contrasena;
}

std::string Usuario::getRango() const {
    return rango;
}

int Usuario::getCapturas() const {
    return capturas;
}

std::string Usuario::getProgreso() const {
    return progreso;
}

// Setters
void Usuario::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

void Usuario::setApellido(const std::string& apellido) {
    this->apellido = apellido;
}

void Usuario::setContrasena(const std::string& contrasena) {
    this->contrasena = contrasena;
}

void Usuario::setRango(const std::string& rango) {
    this->rango = rango;
}

void Usuario::setCapturas(int capturas) {
    this->capturas = capturas;
}

void Usuario::setProgreso(const std::string& progreso) {
    this->progreso = progreso;
}

