#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <Game.hpp>

int get_int(std::string& input, int& i)
{
    std::string digit;
    for (; i < input.size() && input[i] != ','; i++) {
        if (input[i] == ' ')
            continue;
        digit.push_back(input[i]);
    }
    i++;
    return stod(digit);
}

void allocate_memory_for_field(Game::Field_t& map)
{
    map.field = new bool*[map.sizeY];
    for (int i = 0; i < map.sizeY; i++) {
        map.field[i] = new bool[map.sizeX];
        for (int k = 0; k < map.sizeX; k++) {
            map.field[i][k] = 0;
        }
    }
}

void get_map_from_user(Game::Game_window& game_window)
{
    game_window.field.sizeX = 50;
    game_window.field.sizeY = 50;
		game_window.calculate_cell_size();
    allocate_memory_for_field(game_window.field);
    std::cout << "Введите живую клетку в формате: X,Y\nЧтобы закончить ввод "
                 "введите '-1'\n";
    std::string input;
    while (true) {
        std::pair<int, int> coords;
        getline(std::cin, input);
        int i = 0;
        coords.first = get_int(input, i) - 1;
        if (coords.first == -2)
            break;
        coords.second = get_int(input, i) - 1;
        game_window.field.field[coords.second][coords.first]
                = !game_window.field.field[coords.second][coords.first];
    }
}
