#pragma once

#include <Field.hpp>

void game_process(Field &field);

int counting_live_cells(Field &field, int &i, int &k);

void change_state(Field &field);

void print_field(Field &field);
