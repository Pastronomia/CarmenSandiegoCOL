// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#ifndef MISION_DAO_HPP
#define MISION_DAO_HPP

#include <vector>
#include <memory>
#include "BaseDAO.hpp"
#include "Mision.hpp"

class MisionDAO : public BaseDAO {
public:
    MisionDAO(sqlite3* db);

    bool crearTabla();
    bool insertarMision(const Mision& mision);
    bool actualizarMision(const Mision& mision);
    bool eliminarMision(int id);
    std::shared_ptr<Mision> obtenerMisionPorId(int id);
    std::vector<Mision> obtenerTodasLasMisiones();
};

#endif // MISION_DAO_HPP


