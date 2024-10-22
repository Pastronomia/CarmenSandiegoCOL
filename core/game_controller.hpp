// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <memory>
#include <vector>
#include <string>
#include "game_service.hpp"
#include "TTSManager.hpp"

// Declaración hacia adelante para evitar dependencias circulares
class GameWindow;

class GameController {
public:
    GameController(std::shared_ptr<GameService> gameService, std::shared_ptr<TTSManager> ttsManager);

    void iniciarJuego();
    void manejarSeleccionPista(int indicePista);
    void capturarSecuaz();
    void moverSecuazANuevaLocalidad();

private:
    std::shared_ptr<GameService> gameService;
    std::shared_ptr<TTSManager> ttsManager;
    std::shared_ptr<GameWindow> gameWindow;

    void actualizarInterfaz();
    void manejarPistaCorrecta();
    void manejarPistaIncorrecta();
    void mostrarMensaje(const std::string& mensaje);
};

#endif // GAME_CONTROLLER_HPP

