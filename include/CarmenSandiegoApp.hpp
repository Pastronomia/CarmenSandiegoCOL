#ifndef CARMEN_SANDIEGO_APP_HPP
#define CARMEN_SANDIEGO_APP_HPP

#include <gtkmm.h>
#include "DatabaseHandler.hpp"
#include "game_logic.hpp"

class CarmenSandiegoApp : public Gtk::Window {
public:
    CarmenSandiegoApp();

protected:
    Gtk::Box vbox;
    Gtk::Image logo;
    Gtk::Entry username_entry;
    Gtk::Entry password_entry;
    Gtk::Button login_button;
    Gtk::Label status_label;

    Gtk::Box game_box;
    Gtk::Box clue_box;

    DatabaseHandler db_handler;
    GameLogic* game_logic;

    void on_login_button_clicked();
};

#endif  // CARMEN_SANDIEGO_APP_HPP
