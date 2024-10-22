// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include "LocalidadDAO.hpp"
#include <gtkmm.h>
#ifndef LOCALIDAD_DAO_HPP
#define LOCALIDAD_DAO_HPP

#include <vector>
#include <memory>
#include "BaseDAO.hpp"
#include "Localidad.hpp"

class LocalidadDAO : public BaseDAO {
public:
    LocalidadDAO(sqlite3* db);

    bool crearTabla();
    bool insertarLocalidad(const Localidad& localidad);
    bool actualizarLocalidad(const Localidad& localidad);
    bool eliminarLocalidad(int id);
    std::shared_ptr<Localidad> obtenerLocalidadPorId(int id);
    std::vector<Localidad> obtenerTodasLasLocalidades();
};

#endif // LOCALIDAD_DAO_HPP

