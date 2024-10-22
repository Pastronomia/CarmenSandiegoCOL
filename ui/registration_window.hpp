#ifndef REGISTRATION_WINDOW_HPP
#define REGISTRATION_WINDOW_HPP

#include <gtkmm.h>
#include <memory>
#include "UsuarioDAO.hpp"

class RegistrationWindow : public Gtk::Window {
public:
    RegistrationWindow(std::shared_ptr<UsuarioDAO> usuarioDAO);
    virtual ~RegistrationWindow();

private:
    Gtk::Box mainBox;
    Gtk::Entry nombreEntry;
    Gtk::Entry apellidoEntry;
    Gtk::Entry contrasenaEntry;
    Gtk::Button botonRegistrar;
    Gtk::Button botonCancelar;

    std::shared_ptr<UsuarioDAO> usuarioDAO;

    void on_botonRegistrar_clicked();
    void on_botonCancelar_clicked();
};

#endif // REGISTRATION_WINDOW_HPP

