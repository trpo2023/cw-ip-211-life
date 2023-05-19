#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <Game.hpp>

template <typename T1, typename T2>

int counting_live_cells(Game::Field_t& field, T1 i, T2 k)
{
    int count = 0;
    if (i > 0) {
        count += field.field[i - 1][k];
    }
    if (k > 0) {
        count += field.field[i][k - 1];
    }
    if (i < field.sizeX - 1) {
        count += field.field[i + 1][k];
    }
    if (k < field.sizeY - 1) {
        count += field.field[i][k + 1];
    }
    if (i > 0 and k > 0) {
        count += field.field[i - 1][k - 1];
    }
    if (i < field.sizeX - 1 and k > 0) {
        count += field.field[i + 1][k - 1];
    }
    if (i < field.sizeX - 1 and k < field.sizeY - 1) {
        count += field.field[i + 1][k + 1];
    }
    if (i > 0 and k < field.sizeY - 1) {
        count += field.field[i - 1][k + 1];
    }
    return count;
}

void change_state(Game::Field_t& field)
{
    std::vector<std::pair<int, int>> changed_cage;
    for (int i = 0; i < field.sizeX; i++) {
        for (int k = 0; k < field.sizeY; k++) {
            std::pair<int, int> cur_coord;
            if (field.field[i][k]
                and !(counting_live_cells(field, i, k) == 2
                      or counting_live_cells(field, i, k) == 3)) {
                cur_coord.first = i;
                cur_coord.second = k;
                changed_cage.push_back(cur_coord);
            } else if (
                    !field.field[i][k]
                    and counting_live_cells(field, i, k) == 3) {
                cur_coord.first = i;
                cur_coord.second = k;
                changed_cage.push_back(cur_coord);
            }
        }
    }

    for (int i = 0; i < changed_cage.size(); i++) {
        field.field[changed_cage[i].first][changed_cage[i].second]
                = !field.field[changed_cage[i].first][changed_cage[i].second];
    }
}

void print_field(Game::Field_t& field)
{
    for (int i = 0; i < field.sizeY; i++) {
        std::cout << "|\t";
        for (int k = 0; k < field.sizeX; k++) {
            std::cout << field.field[i][k] << "\t";
        }
        std::cout << "|\n";
    }
}

void game_process(Game::Game_window& game_window)
{
    char answer;
    // print_window(game_window);

    do {
        std::cout << "next step?(y/n): ";
        std::cin >> answer;
        print_field(game_window.field);
        std::cout << '\n' << answer;

    } while (answer == 'y');
}
