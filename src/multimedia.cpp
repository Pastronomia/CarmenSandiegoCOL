#include <string>
#include "multimedia.hpp"
#include <cstdlib>

void MultimediaHandler::play_music(const std::string& file_path) {
    std::string command = "play " + file_path;  // Usar 'sox' u otro reproductor en sistemas compatibles
    std::system(command.c_str());
}
