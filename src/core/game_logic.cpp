#include "utils/random_utils.hpp"  // Incluir para usar generarNumeroLocalidadAleatorio
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "dao/PistaDAO.hpp"
#include "dao/SecuazDAO.hpp"
#include "game_logic.hpp"
#include "utils/game_utils.hpp"
#include <gtkmm.h>

std::vector<Pista> seleccionarPistas(const std::vector<Pista>& pistas) {
    std::vector<Pista> seleccionadas;

    if (pistas.size() < 5) {
        throw std::runtime_error("No hay suficientes pistas disponibles para seleccionar.");
    }

    std::sample(pistas.begin(), pistas.begin() + 4, std::back_inserter(seleccionadas), 2, obtenerGeneradorAleatorio());
    seleccionadas.push_back(pistas.back());
    return seleccionadas;
}

void GameLogic::iniciarMision(int localidadId, const Secuaz& secuaz) {
    std::vector<Pista> pistas = PistaDAO::obtenerPistasParaLocalidad(localidadId, db_handler.getDatabase());

    if (pistas.empty()) {
        throw std::runtime_error("No se encontraron pistas para la localidad especificada.");
    }

    int numeroLocalidadAleatorio = generarNumeroLocalidadAleatorio();  // Número aleatorio de 1 a 40
    std::cout << "Número de localidad aleatorio: " << numeroLocalidadAleatorio << std::endl;

    std::vector<Pista> pistasSeleccionadas = seleccionarPistas(pistas);
    mostrarPistasAlJugador(pistasSeleccionadas, secuaz);
}
