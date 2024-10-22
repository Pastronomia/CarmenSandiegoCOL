// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include "main_window.hpp"
#include <iostream>

// Constructor
MainWindow::MainWindow(std::shared_ptr<GameController> gameController)
    : gameController(gameController) {
    set_title(Glib::ustring("Pero... ¿Dónde en Colonia está Carmen Sandiego?"));
    set_default_size(800, 600);

    mainBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
    set_child(mainBox);

    // Botón para iniciar el juego
    botonIniciarJuego.set_label("Iniciar Juego");
    botonIniciarJuego.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_botonIniciarJuego_clicked));
    mainBox.append(botonIniciarJuego, Gtk::PACK_SHRINK);

    // Botón para salir del juego
    botonSalir.set_label("Salir");
    botonSalir.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_botonSalir_clicked));
    mainBox.append(botonSalir, Gtk::PACK_SHRINK);

    
}

// Destructor
MainWindow::~MainWindow() {}

// Función para manejar el botón de "Iniciar Juego"
void MainWindow::on_botonIniciarJuego_clicked() {
    std::cout << "Iniciando el juego..." << std::endl;
    gameController->iniciarJuego();
}

// Función para manejar el botón de "Salir"
void MainWindow::on_botonSalir_clicked() {
    std::cout << "Saliendo del juego..." << std::endl;
    hide();  // Cerrar la ventana
}

