#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <gtkmm.h>
#include <memory>
#include "game_controller.hpp"

class MainWindow : public Gtk::Window {
public:
    MainWindow(std::shared_ptr<GameController> gameController);  // Constructor que recibe GameController
    virtual ~MainWindow();

private:
    Gtk::Box mainBox;
    Gtk::Button botonIniciarJuego;
    Gtk::Button botonSalir;

    std::shared_ptr<GameController> gameController;  // Controlador de juego

    // Funciones para manejar las señales de los botones
    void on_botonIniciarJuego_clicked();
    void on_botonSalir_clicked();
};

#endif // MAIN_WINDOW_HPP

