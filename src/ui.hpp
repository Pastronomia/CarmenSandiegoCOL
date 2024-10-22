#pragma once
#include <gtkmm.h>

class UI {
public:
    UI();
    void showMainMenu();
    void onRegisterButtonClicked();
    void onLoginButtonClicked();
    void onStartGameButtonClicked();

private:
    Gtk::Window window;
    Gtk::Button registerButton, loginButton, startGameButton;
    Gtk::Label messageLabel;
};
