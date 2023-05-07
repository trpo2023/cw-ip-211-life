#pragma once

#include <string>

#include <Field.hpp>

int get_int(std::string &input, int &i);

void allocate_memory_for_field(Field &map);

void get_map_from_user(Field &map);