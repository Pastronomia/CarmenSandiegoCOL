#include "presentation_window.hpp"
#include <glibmm/main.h>
#include "CarmenSandiegoApp.hpp"

PresentationWindow::PresentationWindow() 
    : vbox(Gtk::Orientation::VERTICAL), 
      current_image_index(0) {

    set_title("Carmen Sandiego - Presentación");
    set_default_size(800, 600);

    image_paths = {
        "Multimedia/presentation1.png",
        "Multimedia/presentation2.png",
        "Multimedia/presentation3.png"
    };

    vbox.append(img);
    set_child(vbox);

    show_next_image();
    timer = Glib::signal_timeout().connect(sigc::mem_fun(*this, &PresentationWindow::on_switch_image), 2000);
}

void PresentationWindow::show_next_image() {
    if (current_image_index < static_cast<int>(image_paths.size())) {
        img.set(image_paths[current_image_index]);
        current_image_index++;
    } else {
        switch_to_login();
    }
}

bool PresentationWindow::on_switch_image() {
    show_next_image();
    return true;
}

void PresentationWindow::switch_to_login() {
    timer.disconnect();
    CarmenSandiegoApp* login_window = new CarmenSandiegoApp();
    login_window->present();
    close();
}

PresentationWindow::~PresentationWindow() {}
