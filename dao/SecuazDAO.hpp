// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#ifndef SECUAZ_DAO_HPP
#define SECUAZ_DAO_HPP

#include <vector>
#include <memory>
#include <functional>
#include "BaseDAO.hpp"
#include "Secuaz.hpp"
#include "LocalidadDAO.hpp"

class SecuazDAO : public BaseDAO {
public:
    SecuazDAO(sqlite3* db, std::shared_ptr<LocalidadDAO> localidadDAO);

    // Métodos principales para manipulación de Secuaz en la base de datos
    bool crearTabla();
    bool insertarSecuaz(const Secuaz& secuaz);
    bool actualizarSecuaz(const Secuaz& secuaz);
    bool eliminarSecuaz(int id);
    std::shared_ptr<Secuaz> obtenerSecuazPorId(int id);
    std::vector<Secuaz> obtenerSecuacesNoCapturados();

private:
    // Método auxiliar para ejecutar declaraciones SQL
    bool ejecutarDeclaracion(const char* sql, std::function<void(sqlite3_stmt*)> bindFn = nullptr);

    std::shared_ptr<LocalidadDAO> localidadDAO;
};

#endif // SECUAZ_DAO_HPP

