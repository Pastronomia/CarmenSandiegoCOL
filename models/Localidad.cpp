#include <string>
// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include "Localidad.hpp"

// Constructor
Localidad::Localidad(int id, const std::string& nombre, const std::string& descripcion, double latitud, double longitud)
    : id(id), nombre(nombre), descripcion(descripcion), latitud(latitud), longitud(longitud) {}

// Getters
int Localidad::getId() const {
    return id;
}

const std::string& Localidad::getNombre() const {
    return nombre;
}

const std::string& Localidad::getDescripcion() const {
    return descripcion;
}

double Localidad::getLatitud() const {
    return latitud;
}

double Localidad::getLongitud() const {
    return longitud;
}

// Setters
void Localidad::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

void Localidad::setDescripcion(const std::string& descripcion) {
    this->descripcion = descripcion;
}

void Localidad::setLatitud(double latitud) {
    this->latitud = latitud;
}

void Localidad::setLongitud(double longitud) {
    this->longitud = longitud;
}

// Sobrecarga del operador ==
bool Localidad::operator==(const Localidad& other) const {
    return id == other.id;
}

