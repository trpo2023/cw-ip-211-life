#include <iostream>
#include <string>

#include <Field.hpp>
#include <input.hpp>
#include <logics.hpp>

int main()
{
    Field field;
    get_map_from_user(field);
    game_process(field);
    return 0;
}