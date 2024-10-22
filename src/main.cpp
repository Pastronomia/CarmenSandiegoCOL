// src/main.cpp
#include <locale>
#include <iostream>
// src/main.cpp
#include <gtkmm.h>
#include "ui/presentation_window.hpp"
#include "CarmenSandiegoApp.hpp"

int main() {
    auto app = Gtk::Application::create("com.carmen_sandiego.game");

    PresentationWindow presentation_window;

    return app->run(presentation_window);
}

