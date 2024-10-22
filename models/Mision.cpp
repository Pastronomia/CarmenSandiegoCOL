#include <string>
// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include "Mision.hpp"

Mision::Mision(int id, const std::string& titulo, const std::string& descripcion, const std::string& objetivo, bool completada)
    : id(id), titulo(titulo), descripcion(descripcion), objetivo(objetivo), completada(completada) {}

int Mision::getId() const {
    return id;
}

std::string Mision::getTitulo() const {
    return titulo;
}

std::string Mision::getDescripcion() const {
    return descripcion;
}

std::string Mision::getObjetivo() const {
    return objetivo;
}

bool Mision::isCompletada() const {
    return completada;
}

void Mision::setTitulo(const std::string& titulo) {
    this->titulo = titulo;
}

void Mision::setDescripcion(const std::string& descripcion) {
    this->descripcion = descripcion;
}

void Mision::setObjetivo(const std::string& objetivo) {
    this->objetivo = objetivo;
}

void Mision::setCompletada(bool completada) {
    this->completada = completada;
}

