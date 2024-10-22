#include "ui.h"
#include <gtkmm.h>
#include "multimedia.h"
#include "database.h"

MainWindow::MainWindow() : vbox(Gtk::ORIENTATION_VERTICAL), login_button("Login") {
    // Inicializar multimedia (música e imágenes)
    MultimediaHandler multimedia;
    multimedia.play_background_music("multimedia/background.mp3");

    // Cargar imagen del detective
    Gtk::Image detective_image("multimedia/detective.png");
    vbox.append(detective_image);

    // Entradas de texto para login
    vbox.append(username_entry);
    vbox.append(password_entry);

    vbox.append(login_button);
    login_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_login_button_clicked));

    set_child(vbox);
    
}

void MainWindow::on_login_button_clicked() {
    // Lógica para manejar el login
}
