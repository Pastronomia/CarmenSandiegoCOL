#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "database/DatabaseHandler.hpp"
#include "ui/game_window.hpp"

class GameController {
public:
    GameController(DatabaseHandler& dbHandler);  // Constructor sin TTSManager
    void iniciarJuego();

private:
    GameWindow gameWindow;
    DatabaseHandler& dbHandler;  // Asegurarse de que la referencia est√© declarada
};

#endif // GAME_CONTROLLER_HPP
