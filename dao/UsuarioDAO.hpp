#include <string>
// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#ifndef USUARIODAO_HPP
#define USUARIODAO_HPP

#include "BaseDAO.hpp"
#include "Usuario.hpp"
#include <memory>
#include <vector>

class UsuarioDAO : public BaseDAO {
public:
    UsuarioDAO(sqlite3* db);

    bool crearTabla();
    bool insertarUsuario(const Usuario& usuario);
    bool actualizarUsuario(const Usuario& usuario);
    bool eliminarUsuario(int id);
    std::shared_ptr<Usuario> obtenerUsuarioPorId(int id);
    std::shared_ptr<Usuario> obtenerUsuarioPorNombre(const std::string& nombre);
    std::vector<Usuario> obtenerTodosLosUsuarios();
    bool insertarUsuariosIniciales();

private:
    bool ejecutarConsulta(const std::string& sql, sqlite3_stmt** stmt);
    void ligarValoresUsuario(sqlite3_stmt* stmt, const Usuario& usuario, bool incluirId = false);
};

#endif // USUARIODAO_HPP

