// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
// Archivo: TTSManager.cpp
#include "TTSManager.hpp"
#include <iostream>

// Constructor que recibe la configuración del TTS
TTSManager::TTSManager(const TTSConfig& config)
    : config(config) {
    inicializarTTS();
    aplicarConfiguracion();
}

// Método para convertir texto a voz
void TTSManager::speak(const std::string& texto) {
    std::cout << "TTS: " << texto << std::endl;  // Simulación de TTS
}

// Método para establecer una nueva configuración
void TTSManager::setConfig(const TTSConfig& nuevaConfig) {
    this->config = nuevaConfig;
    aplicarConfiguracion();
}

// Método para obtener la configuración actual
TTSConfig TTSManager::getConfig() const {
    return config;
}

// Inicialización del sistema TTS
void TTSManager::inicializarTTS() {
    std::cout << "Inicializando TTS con idioma: " << config.getIdioma() << std::endl;
}

// Aplicar la configuración del TTS
void TTSManager::aplicarConfiguracion() {
    std::cout << "Configurando TTS - Idioma: " << config.getIdioma()
              << ", Velocidad: " << config.getVelocidad()
              << ", Volumen: " << config.getVolumen() << std::endl;
}

