#include "ui.h"

UI::UI() {
    // Inicializar componentes GTK
    window.set_title(Glib::ustring("Carmen Sandiego Game"));
    registerButton.set_label("Register");
    loginButton.set_label("Login");
    startGameButton.set_label("Start Game");

    // Conectar señales
    registerButton.signal_clicked().connect(sigc::mem_fun(*this, &UI::onRegisterButtonClicked));
    loginButton.signal_clicked().connect(sigc::mem_fun(*this, &UI::onLoginButtonClicked));
    startGameButton.signal_clicked().connect(sigc::mem_fun(*this, &UI::onStartGameButtonClicked));
}

void UI::showMainMenu() {
    Gtk::Box *vbox = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL);
    vbox->append(registerButton);
    vbox->append(loginButton);
    vbox->append(startGameButton);

    window.set_child(*vbox);
    window.show_all();
}

void UI::onRegisterButtonClicked() {
    messageLabel.set_text("Register clicked!");
    // Agregar lógica de registro
}

void UI::onLoginButtonClicked() {
    messageLabel.set_text("Login clicked!");
    // Agregar lógica de login
}

void UI::onStartGameButtonClicked() {
    messageLabel.set_text("Starting the game!");
    // Agregar lógica de inicio de juego
}
