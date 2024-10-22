// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include "game_window.hpp"
#include <iostream>

GameWindow::GameWindow(std::shared_ptr<TTSManager> ttsManager)
    : ttsManager(ttsManager) {  // Inicializar ttsManager
    set_title(Glib::ustring("Pero...¿Dónde en Colonia está Carmen Sandiego?"));
    set_default_size(800, 600);

    mainBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
    set_child(mainBox);

    // Estado del juego
    estadoLabel.set_text("Estado del juego:");
    mainBox.append(estadoLabel, Gtk::PACK_SHRINK);

    // Área de texto para las pistas
    pistasTextView.set_editable(false);
    mainBox.append(pistasTextView);

    // Botones de acción
    botonCapturar.set_label("Capturar Secuaz");
    botonCapturar.signal_clicked().connect(sigc::mem_fun(*this, &GameWindow::on_botonAccion_clicked));
    mainBox.append(botonCapturar, Gtk::PACK_SHRINK);

    botonMover.set_label("Mover Secuaz");
    botonMover.signal_clicked().connect(sigc::mem_fun(*this, &GameWindow::on_botonAccion_clicked));
    mainBox.append(botonMover, Gtk::PACK_SHRINK);

    
}

// Destructor
GameWindow::~GameWindow() {}

// Mostrar pistas en el TextView
void GameWindow::mostrarPistas(const std::vector<std::string>& pistas) {
    auto buffer = pistasTextView.get_buffer();
    buffer->set_text("");  // Limpiar el buffer

    for (const auto& pista : pistas) {
        buffer->insert(buffer->end(), pista + "\n");
    }
}

// Actualizar el estado del juego
void GameWindow::actualizarEstado(const std::string& estado) {
    estadoLabel.set_text("Estado del juego: " + estado);
}

// Mostrar mensaje usando TTS y un diálogo
void GameWindow::mostrarMensaje(const std::string& mensaje) {
    ttsManager->speak(mensaje);  // Usar ttsManager para hablar
    Gtk::MessageDialog dialog(*this, mensaje);
    dialog.run();
}

// Manejar evento de botones Capturar y Mover
void GameWindow::on_botonAccion_clicked() {
    Gtk::Button* button = dynamic_cast<Gtk::Button*>(get_focus_widget());
    if (button == &botonCapturar) {
        std::cout << "Botón Capturar Secuaz presionado" << std::endl;
    } else if (button == &botonMover) {
        std::cout << "Botón Mover Secuaz presionado" << std::endl;
    }
}

// Manejar teclas S, D, F y clics en botones de pista
bool GameWindow::on_key_press_event(GdkEventKey* event) {
    constexpr guint tecla_s = GDK_KEY_s;
    constexpr guint tecla_d = GDK_KEY_d;
    constexpr guint tecla_f = GDK_KEY_f;

    switch (event->keyval) {
        case tecla_s:
            on_button_pista_clicked(pista_1_button);
            break;
        case tecla_d:
            on_button_pista_clicked(pista_2_button);
            break;
        case tecla_f:
            on_button_pista_clicked(pista_3_button);
            break;
        default:
            return Gtk::Window::on_key_press_event(event); // Mantener el manejo de otros eventos de teclas
    }
    return true;  // Evitar otros manejadores para las teclas S, D, F
}

// Lógica cuando se selecciona una pista
void GameWindow::on_button_pista_clicked(Gtk::Button* pista_button) {
    if (pista_button == pista_correcta_button) {
        mostrarMensaje("Adelante, te estás acercando.");
    } else {
        mostrarMensaje("Tienes otra oportunidad. Cuídala.");
    }
}
