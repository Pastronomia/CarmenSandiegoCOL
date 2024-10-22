#include "core/game_controller.hpp"

// Constructor actualizado sin TTSManager ni gameService
GameController::GameController(DatabaseHandler& dbHandler)
    : dbHandler(dbHandler), gameWindow() {  // Asegurarse de inicializar la referencia dbHandler
    // Lógica de inicialización si es necesaria
}

void GameController::iniciarJuego() {
    gameWindow.show();
}
