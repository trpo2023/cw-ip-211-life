#pragma once

#include <string>

#include <Game.hpp>

int get_int(std::string& input, int& i);

void allocate_memory_for_field(Game::Field_t& map);

void get_map_from_user(Game::Game_window& map);