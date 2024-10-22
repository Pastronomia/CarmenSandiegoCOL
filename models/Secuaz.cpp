#include <string>
// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include "Secuaz.hpp"

// Implementación de la clase Secuaz

// Constructor por defecto
Secuaz::Secuaz() : id(0), nombre(""), habilidad(""), peligrosidad(0), localidad(nullptr), capturado(false) {}

// Constructor con parámetros
Secuaz::Secuaz(int id, const std::string& nombre, const std::string& habilidad, int peligrosidad, std::shared_ptr<Localidad> localidad, bool capturado)
    : id(id), nombre(nombre), habilidad(habilidad), peligrosidad(peligrosidad), localidad(localidad), capturado(capturado) {}

// Getters
int Secuaz::getId() const {
    return id;
}

std::string Secuaz::getNombre() const {
    return nombre;
}

std::string Secuaz::getHabilidad() const {
    return habilidad;
}

int Secuaz::getPeligrosidad() const {
    return peligrosidad;
}

std::shared_ptr<Localidad> Secuaz::getLocalidad() const {
    return localidad;
}

bool Secuaz::isCapturado() const {
    return capturado;
}

// Setters
void Secuaz::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

void Secuaz::setHabilidad(const std::string& habilidad) {
    this->habilidad = habilidad;
}

void Secuaz::setPeligrosidad(int peligrosidad) {
    this->peligrosidad = peligrosidad;
}

void Secuaz::setLocalidad(std::shared_ptr<Localidad> localidad) {
    this->localidad = localidad;
}

void Secuaz::setCapturado(bool capturado) {
    this->capturado = capturado;
}

