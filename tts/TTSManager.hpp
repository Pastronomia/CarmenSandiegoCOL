// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
// Archivo: TTSManager.hpp
#ifndef TTSMANAGER_HPP
#define TTSMANAGER_HPP

#include <string>
#include "TTSConfig.hpp"

class TTSManager {
public:
    TTSManager(const TTSConfig& config);  // Constructor que recibe la configuración de TTS

    void speak(const std::string& texto);  // Método para convertir texto a voz
    void setConfig(const TTSConfig& config);  // Cambiar la configuración del TTS
    TTSConfig getConfig() const;  // Obtener la configuración actual

private:
    TTSConfig config;  // Almacena la configuración del TTS

    void inicializarTTS();  // Inicializa el sistema de TTS
    void aplicarConfiguracion();  // Aplica la configuración al sistema TTS
};

#endif // TTSMANAGER_HPP

