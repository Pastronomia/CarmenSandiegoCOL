#ifndef MULTIMEDIA_HANDLER_HPP
#define MULTIMEDIA_HANDLER_HPP

#include <string>

class MultimediaHandler {
public:
    MultimediaHandler();
    void cargar_imagen(const std::string& ruta_imagen);
    void reproducir_sonido(const std::string& ruta_sonido);
    void detener_sonido();

    // Otros métodos para manejar multimedia
};

#endif  // MULTIMEDIA_HANDLER_HPP
