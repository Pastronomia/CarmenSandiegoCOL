// Archivo: result_window.cpp
#include "result_window.hpp"
#include <gtkmm/messagedialog.h>
#include <iostream>

ResultWindow::ResultWindow(const std::vector<Jugador>& jugadores, const std::string& usuarioActual)
    : jugadores(jugadores), usuarioActual(usuarioActual) {
    
    set_title(Glib::ustring("Resultados del Juego"));
    set_default_size(600, 400);

    // Crear lista de puntajes
    liststore = Gtk::ListStore::create();
    treeview.set_model(liststore);
    
    // Añadir columnas a la tabla
    treeview.append_column("Jugador", ...);  // Añadir el nombre del jugador
    treeview.append_column("Rango", ...);    // Añadir el rango del jugador
    treeview.append_column("Puntaje", ...);  // Añadir el puntaje

    // Llenar la tabla con los datos de los jugadores
    for (const auto& jugador : jugadores) {
        Gtk::TreeModel::Row row = *(liststore->append());
        row[...];  // Asignar nombre del jugador
        row[...];  // Asignar rango
        row[...];  // Asignar puntaje

        // Hacer que el clic en el jugador dispare una señal
        if (jugador.nombre == usuarioActual) {
            treeview.signal_row_activated().connect(
                sigc::bind(sigc::mem_fun(*this, &ResultWindow::on_jugador_clicked), jugador.nombre));
        }
    }

    set_child(treeview);
    
}

ResultWindow::~ResultWindow() {}

void ResultWindow::on_jugador_clicked(const std::string& nombreJugador) {
    if (nombreJugador == usuarioActual) {
        // Mostrar las respuestas equivocadas y correctas del usuario actual
        for (const auto& jugador : jugadores) {
            if (jugador.nombre == nombreJugador) {
                std::string detalle = "Respuestas incorrectas y correctas:\n";
                for (const auto& respuesta : jugador.respuestas) {
                    detalle += "Equivocada: " + respuesta.first + ", Correcta: " + respuesta.second + "\n";
                }
                Gtk::MessageDialog dialog(*this, detalle);
                dialog.run();
                break;
            }
        }
    }
}
