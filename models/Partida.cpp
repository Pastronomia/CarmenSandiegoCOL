// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include "Partida.hpp"

// Constructor
Partida::Partida(int id, int usuarioId, int secuazId, const std::string& estado, int intentos)
    : id(id), usuarioId(usuarioId), secuazId(secuazId), estado(estado), intentos(intentos) {}

// Getters
int Partida::getId() const {
    return id;
}

int Partida::getUsuarioId() const {
    return usuarioId;
}

int Partida::getSecuazId() const {
    return secuazId;
}

std::string Partida::getEstado() const {
    return estado;
}

int Partida::getIntentos() const {
    return intentos;
}

// Setters
void Partida::setUsuarioId(int usuarioId) {
    this->usuarioId = usuarioId;
}

void Partida::setSecuazId(int secuazId) {
    this->secuazId = secuazId;
}

void Partida::setEstado(const std::string& estado) {
    this->estado = estado;
}

void Partida::setIntentos(int intentos) {
    this->intentos = intentos;
}

