#include "game_logic.hpp"  // Incluye el encabezado de GameLogic
#include "DatabaseHandler.hpp"  // Asegúrate de que DatabaseHandler está correctamente implementado
#include "MultimediaHandler.hpp"  // Asegúrate de tener esta clase implementada

// Implementación del constructor de GameLogic
GameLogic::GameLogic(DatabaseHandler &db, MultimediaHandler &mm_handler)
    : db_handler(db), mm_handler(mm_handler) {
    // Inicializa los manejadores de la lógica del juego aquí si es necesario
}
