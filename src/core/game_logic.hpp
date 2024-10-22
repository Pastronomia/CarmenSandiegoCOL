#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <string>
#include <vector>
#include "DatabaseHandler.hpp"

// Clase que maneja la lógica del juego
class GameLogic {
public:
    GameLogic(DatabaseHandler& dbHandler);

    // Métodos principales del juego
    std::vector<std::string> obtenerPistas(int localidadId);
    bool verificarRespuesta(int localidadId, const std::string& respuesta);

private:
    DatabaseHandler& dbHandler;
};

#endif // GAME_LOGIC_HPP
