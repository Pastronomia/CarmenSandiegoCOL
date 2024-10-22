// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#ifndef GAME_SERVICE_HPP
#define GAME_SERVICE_HPP

#include <vector>
#include <memory>
#include "LocalidadDAO.hpp"
#include "PistaDAO.hpp"
#include "SecuazDAO.hpp"
#include "Pista.hpp"
#include "Localidad.hpp"
#include "Secuaz.hpp"

class GameService {
public:
    GameService(std::shared_ptr<PistaDAO> pistaDAO, std::shared_ptr<LocalidadDAO> localidadDAO, std::shared_ptr<SecuazDAO> secuazDAO);

    void iniciarNuevaPartida();
    std::vector<Pista> obtenerPistasActuales();
    bool manejarSeleccionPista(const Pista& pista);
    void capturarSecuazActual();
    void moverSecuazANuevaLocalidad();
    bool haPerdidoJuego() const;
    bool esCapturaExitosa() const;
    std::string obtenerEstadoJuego() const;

private:
    std::shared_ptr<PistaDAO> pistaDAO;
    std::shared_ptr<LocalidadDAO> localidadDAO;
    std::shared_ptr<SecuazDAO> secuazDAO;

    Localidad localidadActual;
    Secuaz secuazActual;
    int erroresConsecutivos;

    void seleccionarNuevoSecuaz();
};

#endif // GAME_SERVICE_HPP

