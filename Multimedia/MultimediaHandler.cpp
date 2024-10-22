#include "MultimediaHandler.hpp"
#include <iostream>

MultimediaHandler::MultimediaHandler() {
    // Constructor - Inicialización de recursos
}

void MultimediaHandler::cargar_imagen(const std::string& ruta_imagen) {
    std::cout << "Cargando imagen desde: " << ruta_imagen << std::endl;
    // Código para cargar y mostrar la imagen
}

void MultimediaHandler::reproducir_sonido(const std::string& ruta_sonido) {
    std::cout << "Reproduciendo sonido desde: " << ruta_sonido << std::endl;
    // Código para reproducir el sonido
}

void MultimediaHandler::detener_sonido() {
    std::cout << "Deteniendo el sonido." << std::endl;
    // Código para detener el sonido
}
