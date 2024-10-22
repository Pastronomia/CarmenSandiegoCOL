#include <gtkmm.h>
#include <iostream>
#include <sqlite3.h>
#include <gstreamer-1.0/gst/gst.h>
#include <random>

// Ventana de bienvenida y presentación
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

        auto auth_window = new AuthWindow();
        auth_window->show();
    }

    Gtk::Button m_button;
};

// Ventana de autenticación de usuarios
class AuthWindow : public Gtk::Window {
public:
    AuthWindow() : m_button_login("Iniciar sesión"), m_button_register("Registrarse") {
        set_title("Autenticación de Usuario");
        set_default_size(400, 300);

        auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 10);
        set_child(*vbox);

        vbox->append(m_entry_user);
        vbox->append(m_entry_pass);
        vbox->append(m_button_login);
        vbox->append(m_button_register);

        m_button_login.signal_clicked().connect(sigc::mem_fun(*this, &AuthWindow::on_login_clicked));
        m_button_register.signal_clicked().connect(sigc::mem_fun(*this, &AuthWindow::on_register_clicked));

        // Abrir la base de datos SQLite
        if (sqlite3_open("carmen_sandiego.db", &db)) {
            std::cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        }
    }

    ~AuthWindow() {
        sqlite3_close(db);
    }

protected:
    Gtk::Entry m_entry_user;
    Gtk::Entry m_entry_pass;
    Gtk::Button m_button_login;
    Gtk::Button m_button_register;
    sqlite3 *db;

    void on_login_clicked() {
        std::string user = m_entry_user.get_text();
        std::string pass = m_entry_pass.get_text();

        if (authenticate_user(user, pass)) {
            std::cout << "Inicio de sesión exitoso" << std::endl;
            hide();
            // Mostrar ventana de juego
            auto game_window = new GameWindow(db);
            game_window->show();
        } else {
            std::cerr << "Error de autenticación" << std::endl;
        }
    }

    void on_register_clicked() {
        std::string user = m_entry_user.get_text();
        std::string pass = m_entry_pass.get_text();

        if (register_user(user, pass)) {
            std::cout << "Usuario registrado exitosamente" << std::endl;
        } else {
            std::cerr << "Error al registrar usuario" << std::endl;
        }
    }

    bool authenticate_user(const std::string &username, const std::string &password) {
        std::string query = "SELECT * FROM users WHERE username = ? AND password = ?";
        sqlite3_stmt *stmt;
        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                sqlite3_finalize(stmt);
                return true;
            }
        }
        sqlite3_finalize(stmt);
        return false;
    }

    bool register_user(const std::string &username, const std::string &password) {
        std::string query = "INSERT INTO users (username, password) VALUES (?, ?)";
        sqlite3_stmt *stmt;
        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_DONE) {
                sqlite3_finalize(stmt);
                return true;
            }
        }
        sqlite3_finalize(stmt);
        return false;
    }
};

// Ventana de juego donde se muestran pistas y secuaces
class GameWindow : public Gtk::Window {
public:
    GameWindow(sqlite3 *db) : m_button("Generar Pistas") {
        set_title("Juego Carmen Sandiego");
        set_default_size(800, 600);

        this->db = db;
        auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 10);
        set_child(*vbox);

        vbox->append(m_button);
        vbox->append(m_label);

        m_button.signal_clicked().connect(sigc::mem_fun(*this, &GameWindow::on_button_clicked));
    }

protected:
    Gtk::Button m_button;
    Gtk::Label m_label;
    sqlite3 *db;

    void on_button_clicked() {
        std::string pista = get_random_pista();
        std::cout << "Pista generada: " << pista << std::endl;
        m_label.set_text(pista);
    }

    // Obtener una pista aleatoria de la base de datos
    std::string get_random_pista() {
        std::string query = "SELECT pista FROM pistas ORDER BY RANDOM() LIMIT 1";
        sqlite3_stmt *stmt;
        std::string pista;

        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                pista = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            }
        }

        sqlite3_finalize(stmt);
        return pista;
    }
};

// Función para iniciar GStreamer y reproducir música de fondo
void play_background_music(const std::string &file_path) {
    GstElement *pipeline = gst_parse_launch(("playbin uri=file://" + file_path).c_str(), nullptr);
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
}

// Función principal que ejecuta la aplicación
int main(int argc, char *argv[]) {
    // Inicializar GStreamer
    gst_init(&argc, &argv);

    auto app = Gtk::Application::create("org.gtkmm.carmensandiego");

    // Iniciar música de fondo
    play_background_music("assets/AUDIO/CSD.mp3");

    // Iniciar la ventana de bienvenida
    WelcomeWindow welcome_window;

    return app->run(welcome_window);
}
