#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include "DatabaseHandler.hpp"
#include "MultimediaHandler.hpp"

class GameLogic {
public:
    GameLogic(DatabaseHandler &db, MultimediaHandler &mm_handler);

private:
    DatabaseHandler &db_handler;
    MultimediaHandler &mm_handler;
};

#endif  // GAME_LOGIC_HPP
