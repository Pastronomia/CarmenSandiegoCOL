// ui/presentation_window.hpp
#ifndef PRESENTATION_WINDOW_HPP
#define PRESENTATION_WINDOW_HPP

#include <gtkmm.h>
#include <vector>

class PresentationWindow : public Gtk::Window {
public:
    PresentationWindow();
    virtual ~PresentationWindow();

protected:
    void show_next_image();
    bool on_switch_image();

    Gtk::Box vbox;
    Gtk::Image img;

    sigc::connection timer;
    std::vector<std::string> image_paths;
    int current_image_index;

    void switch_to_login();
};

#endif // PRESENTATION_WINDOW_HPP
