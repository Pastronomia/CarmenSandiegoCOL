// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
// Archivo: TTSConfig.hpp
#ifndef TTSCONFIG_HPP
#define TTSCONFIG_HPP

#include <string>

class TTSConfig {
public:
    TTSConfig(const std::string& idioma, int velocidad, int volumen);

    std::string getIdioma() const;
    int getVelocidad() const;
    int getVolumen() const;

    void setIdioma(const std::string& idioma);
    void setVelocidad(int velocidad);
    void setVolumen(int volumen);

private:
    std::string idioma;
    int velocidad;
    int volumen;
};

#endif // TTSCONFIG_HPP

