// Cabecera añadida automáticamente por torquemada.py
#include "PistaDAO.hpp"
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include "game_controller.hpp"
#include "game_window.hpp"
#include <iostream>
#include <vector>

// Create a TTSConfig and pass it to TTSManager
TTSConfig config("es", 100, 50);  // Configuration with language, speed, and volume

// Constructor of GameController, initializes gameService, ttsManager, and GameWindow
GameController::GameController(std::shared_ptr<GameService> gameService, std::shared_ptr<TTSManager> ttsManager)
    : gameService(gameService), ttsManager(ttsManager) {
    // Pass the ttsManager to the GameWindow constructor
    gameWindow = std::make_shared<GameWindow>(ttsManager);
}

// Starts a new game and updates the interface
void GameController::iniciarJuego() {
    ttsManager->speak("Bienvenido a: ¿Pero dónde, en Colonia, está Carmen Sandiego?");
    gameService->iniciarNuevaPartida();
    actualizarInterfaz();
}

// Método para convertir Pista a std::string
std::string pistaToString(const Pista& pista) {
    return pista.getDescripcion();
}

// Handles the player's clue selection
void GameController::manejarSeleccionPista(int indicePista) {
    auto pistas = gameService->obtenerPistasActuales();
    if (indicePista < 0 || indicePista >= pistas.size()) {
        mostrarMensaje("Selección no válida.");
        return;
    }

    if (gameService->manejarSeleccionPista(pistas[indicePista])) {
        manejarPistaCorrecta();
    } else {
        manejarPistaIncorrecta();
    }
}

// Handles correct clue logic
void GameController::manejarPistaCorrecta() {
    mostrarMensaje("¡Correcto! Te estás acercando al secuaz.");
    if (gameService->esCapturaExitosa()) {
        capturarSecuaz();
    } else {
        moverSecuazANuevaLocalidad();
    }
}

// Handles incorrect clue logic
void GameController::manejarPistaIncorrecta() {
    mostrarMensaje("Pista incorrecta. El secuaz se está escapando.");
    if (gameService->haPerdidoJuego()) {
        mostrarMensaje("Has perdido. Intenta nuevamente.");
        // Logic to restart the game can be added here
    } else {
        moverSecuazANuevaLocalidad();
    }
}

// Captures the current henchman
void GameController::capturarSecuaz() {
    mostrarMensaje("¡Has capturado al secuaz!");
    gameService->capturarSecuazActual();
    actualizarInterfaz();
}

// Moves the henchman to a new location
void GameController::moverSecuazANuevaLocalidad() {
    gameService->moverSecuazANuevaLocalidad();
    actualizarInterfaz();
}

// Updates the interface with new clues and game status
void GameController::actualizarInterfaz() {
    auto pistas = gameService->obtenerPistasActuales();
    std::vector<std::string> pistasStr;
    for (const auto& pista : pistas) {
        pistasStr.push_back(pistaToString(pista));
    }

    gameWindow->mostrarPistas(pistasStr);
    gameWindow->actualizarEstado(gameService->obtenerEstadoJuego());
}

// Displays a message on both the console and the GameWindow, and speaks it using TTS
void GameController::mostrarMensaje(const std::string& mensaje) {
    ttsManager->speak(mensaje);
    std::cout << mensaje << std::endl;
    gameWindow->mostrarMensaje(mensaje);
}

