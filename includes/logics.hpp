#pragma once

#include <Field.hpp>

template <typename T1, typename T2>
int counting_live_cells(Field& field, T1 i, T2 k);

void game_process(Field& field);

void change_state(Field& field);

void print_field(Field& field);
