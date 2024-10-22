// ui/presentation_window.cpp

#include "presentation_window.hpp"
#include <iostream>
#include <glibmm/main.h>

PresentationWindow::PresentationWindow() 
    : vbox(Gtk::Orientation::VERTICAL), button("Iniciar Juego"), current_image_index(0) {

    set_title("Bienvenido a Carmen Sandiego");
    set_default_size(600, 400);

    // Añadir texto de bienvenida
    label.set_text("Bienvenido al juego de: Pero, ¿Dónde, en Colonia, está Carmen Sandiego?");
    label.set_halign(Gtk::Align::CENTER);
    label.set_margin_top(10);
    label.set_margin_bottom(20);
    vbox.append(label);

    // Cargar imágenes para el carrusel
    image_paths = {
        "Multimedia/DetectiveJunior.png",
        "Multimedia/DetectiveExperto.png",
        "Multimedia/Betosecreto.png",
        "Multimedia/EllaBella.png"
    };
    img.set(image_paths[current_image_index]);
    vbox.append(img);

    // Configurar el temporizador para cambiar de imagen cada 1,5 segundos
    timer = Glib::signal_timeout().connect(sigc::mem_fun(*this, &PresentationWindow::on_switch_image), 1500);

    // Añadir botón de iniciar
    button.signal_clicked().connect(sigc::mem_fun(*this, &PresentationWindow::on_button_clicked));
    vbox.append(button);

    // Establecer el layout
    set_child(vbox);

    // Iniciar la música
    play_music();
}

PresentationWindow::~PresentationWindow() {
    // Desconectar el temporizador al cerrar la ventana
    timer.disconnect();
}

void PresentationWindow::on_button_clicked() {
    // Aquí se cierra la ventana de presentación y se inicia el juego
    std::cout << "Iniciar juego presionado" << std::endl;
    close();
}

bool PresentationWindow::on_switch_image() {
    // Cambiar a la siguiente imagen del carrusel
    current_image_index = (current_image_index + 1) % image_paths.size();
    img.set(image_paths[current_image_index]);
    return true; // Mantener el temporizador activo
}

void PresentationWindow::play_music() {
    // Inicializar GStreamer
    gst_init(nullptr, nullptr);

    // Crear un pipeline de reproducción para el archivo MP3
    GstElement *pipeline = gst_parse_launch("playbin uri=file:///ruta/absoluta/Multimedia/CSD.mp3", nullptr);
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
}
