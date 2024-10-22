#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include <gtkmm.h>
#include <vector>
#include <string>
#include <memory>
#include "TTSManager.hpp"  // Incluir TTSManager

class GameWindow : public Gtk::Window {
public:
    GameWindow(std::shared_ptr<TTSManager> ttsManager);  // Añadir ttsManager al constructor
    virtual ~GameWindow();

    void mostrarPistas(const std::vector<std::string>& pistas);
    void actualizarEstado(const std::string& estado);
    void mostrarMensaje(const std::string& mensaje);

private:
    Gtk::Box mainBox;
    Gtk::Label estadoLabel;
    Gtk::TextView pistasTextView;
    Gtk::Button botonCapturar;
    Gtk::Button botonMover;

    std::shared_ptr<TTSManager> ttsManager;  // Declarar el TTSManager aquí

    void on_botonCapturar_clicked();
    void on_botonMover_clicked();
};

#endif // GAME_WINDOW_HPP

