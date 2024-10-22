// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#ifndef PARTIDA_DAO_HPP
#define PARTIDA_DAO_HPP

#include <vector>
#include <memory>
#include "BaseDAO.hpp"
#include "Partida.hpp"

class PartidaDAO : public BaseDAO {
public:
    PartidaDAO(sqlite3* db);

    bool crearTabla();
    bool insertarPartida(const Partida& partida);
    bool actualizarPartida(const Partida& partida);
    bool eliminarPartida(int id);
    std::shared_ptr<Partida> obtenerPartidaPorId(int id);
    std::vector<Partida> obtenerTodasLasPartidas();
};

#endif // PARTIDA_DAO_HPP

