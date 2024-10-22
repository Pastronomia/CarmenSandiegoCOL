#include <gtkmm.h>
#include <iostream>

// Clase WelcomeWindow que incluye la funcionalidad del botón para iniciar presentación
class WelcomeWindow : public Gtk::Window {
public:
    WelcomeWindow() : m_button("Iniciar presentación") {
        set_title("Bienvenido a Carmen Sandiego");
        set_default_size(800, 600);

        auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 10);
        set_child(*vbox);

        vbox->append(m_button);
        m_button.signal_clicked().connect(sigc::mem_fun(*this, &WelcomeWindow::on_button_clicked));
    }

protected:
    void on_button_clicked() {
        std::cout << "Presentación iniciada" << std::endl;
        hide();  // Ocultar la ventana actual
        // Lógica para cambiar a la siguiente ventana
    }

    Gtk::Button m_button;
};

// Función principal que ejecuta la aplicación
int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create("org.gtkmm.carmensandiego");

    WelcomeWindow welcome_window;

    return app->run(welcome_window);
}
