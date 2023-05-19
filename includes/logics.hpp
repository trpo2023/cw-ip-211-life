#pragma once

#include <Game.hpp>

template <typename T1, typename T2>
int counting_live_cells(Game::Field_t& field, T1 i, T2 k);

void game_process(Game::Game_window& field);

void change_state(Game::Field_t& field);

void print_field(Game::Field_t& field);
