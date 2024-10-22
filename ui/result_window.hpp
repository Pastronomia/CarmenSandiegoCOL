// Archivo: result_window.hpp
#ifndef RESULT_WINDOW_HPP
#define RESULT_WINDOW_HPP

#include <gtkmm.h>
#include <vector>
#include <string>

struct Jugador {
    std::string nombre;
    std::string rango;
    int puntaje;
    std::vector<std::pair<std::string, std::string>> respuestas;  // (equivocada, correcta)
};

class ResultWindow : public Gtk::Window {
public:
    ResultWindow(const std::vector<Jugador>& jugadores, const std::string& usuarioActual);
    virtual ~ResultWindow();

protected:
    void on_jugador_clicked(const std::string& nombreJugador);  // Muestra detalles del jugador

    Gtk::Box vbox;
    Gtk::TreeView treeview;
    Glib::RefPtr<Gtk::ListStore> liststore;

    std::vector<Jugador> jugadores;
    std::string usuarioActual;
};

#endif
