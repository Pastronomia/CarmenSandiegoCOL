#include <gtkmm.h>
#include "CarmenSandiegoApp.hpp"

CarmenSandiegoApp::CarmenSandiegoApp()
    : vbox(Gtk::Orientation::VERTICAL),
      login_button("Login"),
      db_handler("H:/TALLER UNO I/SQLite/carmen_sandiego.db"),
      game_logic(nullptr) {

    set_title("Carmen Sandiego - Login");
    set_default_size(400, 300);

    logo.set("Multimedia/csd.png");
    vbox.append(logo);

    username_entry.set_placeholder_text("Nombre");
    password_entry.set_placeholder_text("Contraseña");
    password_entry.set_visibility(false);
    vbox.append(username_entry);
    vbox.append(password_entry);

    vbox.append(login_button);
    login_button.signal_clicked().connect(sigc::mem_fun(*this, &CarmenSandiegoApp::on_login_button_clicked));

    vbox.append(status_label);

    set_child(vbox);
}

void CarmenSandiegoApp::on_login_button_clicked() {
    Glib::ustring username = username_entry.get_text();
    Glib::ustring password = password_entry.get_text();

    if (db_handler.autenticar_usuario(username, password)) {
        status_label.set_text("¡Bienvenido, " + username + "!");
    } else {
        status_label.set_text("Error: Usuario o contraseña incorrectos.");
    }
}
