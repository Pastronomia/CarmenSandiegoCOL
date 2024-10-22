#ifndef PISTADAO_HPP
#define PISTADAO_HPP

#include <sqlite3.h>
#include <memory>
#include <vector>
#include "models/Pista.hpp" 
#include "BaseDAO.hpp"

class PistaDAO : public BaseDAO {
public:
    PistaDAO(sqlite3* db);
    bool crearTabla();
    bool insertarPista(const Pista& pista);
    bool actualizarPista(const Pista& pista);
    bool eliminarPista(int id);
    std::shared_ptr<Pista> obtenerPistaPorId(int id);
    std::vector<Pista> obtenerPistasPorLocalidad(int localidadId);
    std::vector<Pista> obtenerPistasAleatoriasPorLocalidad(int localidadId, int cantidad);
};

#endif // PISTADAO_HPP
