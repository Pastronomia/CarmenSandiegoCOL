// Cabecera añadida automáticamente por torquemada.py
#include "PistaDAO.hpp"
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include "game_service.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include "LocalidadDAO.hpp"

// Constructor
GameService::GameService(std::shared_ptr<PistaDAO> pistaDAO, std::shared_ptr<LocalidadDAO> localidadDAO, std::shared_ptr<SecuazDAO> secuazDAO)
    : pistaDAO(pistaDAO), localidadDAO(localidadDAO), secuazDAO(secuazDAO), erroresConsecutivos(0) {
    iniciarNuevaPartida();
}

// Inicia una nueva partida seleccionando un nuevo secuaz
void GameService::iniciarNuevaPartida() {
    seleccionarNuevoSecuaz();
}

// Obtener pistas para la localidad actual
std::vector<Pista> GameService::obtenerPistasActuales() {
    return pistaDAO->obtenerPistasPorLocalidad(localidadActual.getId());
}

// Maneja la selección de una pista, verificando si es correcta y actualizando el estado del juego
bool GameService::manejarSeleccionPista(const Pista& pista) {
    if (pista.esCorrecta()) {
        if (esCapturaExitosa()) {
            return true; // Captura exitosa
        }
        moverSecuazANuevaLocalidad();
        return false; // Pista correcta pero no captura
    } else {
        erroresConsecutivos++;
        return false; // Pista incorrecta
    }
}

// Capturar al secuaz actual, marcándolo como capturado y seleccionando uno nuevo
void GameService::capturarSecuazActual() {
    secuazActual.setCapturado(true);
    secuazDAO->actualizarSecuaz(secuazActual);
    seleccionarNuevoSecuaz();
}

// Mueve al secuaz actual a una nueva localidad aleatoria
void GameService::moverSecuazANuevaLocalidad() {
    auto localidades = localidadDAO->obtenerTodasLasLocalidades();
    localidades.erase(std::remove(localidades.begin(), localidades.end(), localidadActual), localidades.end());

    if (!localidades.empty()) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(localidades.begin(), localidades.end(), g);

        auto nuevaLocalidad = std::make_shared<Localidad>(localidades.front());
        secuazActual.setLocalidad(nuevaLocalidad);
        secuazDAO->actualizarSecuaz(secuazActual);
        localidadActual = *nuevaLocalidad;
    } else {
        std::cerr << "No hay localidades disponibles para mover al secuaz." << std::endl;
    }
}

// Verifica si el jugador ha perdido (tres errores consecutivos)
bool GameService::haPerdidoJuego() const {
    return erroresConsecutivos >= 3;
}

// Verifica si la captura del secuaz ha sido exitosa
bool GameService::esCapturaExitosa() const {
    return localidadActual.getId() == secuazActual.getLocalidad()->getId();
}

// Devuelve el estado actual del juego como una cadena
std::string GameService::obtenerEstadoJuego() const {
    return "Secuaz: " + secuazActual.getNombre() + ", Localidad: " + localidadActual.getNombre();
}

// Selecciona un nuevo secuaz de entre los que no han sido capturados
void GameService::seleccionarNuevoSecuaz() {
    auto secuacesDisponibles = secuazDAO->obtenerSecuacesNoCapturados();
    if (!secuacesDisponibles.empty()) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(secuacesDisponibles.begin(), secuacesDisponibles.end(), g);

        secuazActual = secuacesDisponibles.front();
        localidadActual = *(secuazActual.getLocalidad());
    } else {
        std::cerr << "No hay secuaces disponibles para seleccionar." << std::endl;
    }
}

