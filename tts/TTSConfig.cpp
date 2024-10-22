// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
// tts/TTSConfig.cpp
#include "TTSConfig.hpp"

// Constructor
TTSConfig::TTSConfig(const std::string& idioma, int velocidad, int volumen)
    : idioma(idioma), velocidad(velocidad), volumen(volumen) {}

// Getters
std::string TTSConfig::getIdioma() const {
    return idioma;
}

int TTSConfig::getVelocidad() const {
    return velocidad;
}

int TTSConfig::getVolumen() const {
    return volumen;
}

// Setters
void TTSConfig::setIdioma(const std::string& idioma) {
    this->idioma = idioma;
}

void TTSConfig::setVelocidad(int velocidad) {
    this->velocidad = velocidad;
}

void TTSConfig::setVolumen(int volumen) {
    this->volumen = volumen;
}

