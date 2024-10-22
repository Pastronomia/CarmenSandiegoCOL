#ifndef WELCOME_WINDOW_HPP
#define WELCOME_WINDOW_HPP

#include <gtkmm.h>

class WelcomeWindow : public Gtk::Window {
public:
    WelcomeWindow();
    virtual ~WelcomeWindow() = default;

protected:
    void on_button_clicked();  // Función para manejar el evento del clic en el botón

    Gtk::Button m_button;  // Botón en la ventana de bienvenida
};

#endif // WELCOME_WINDOW_HPP
