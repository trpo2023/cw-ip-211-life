#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <Game.hpp>

template <typename T1, typename T2>
int Game::Logic::counting_live_cells(Game::Field_t& field, T1 i, T2 k)
{
    int count = 0;
    if (i > 0) {
        count += field.field[i - 1][k];
    }
    if (k > 0) {
        count += field.field[i][k - 1];
    }
    if (i < field.sizeY - 1) {
        count += field.field[i + 1][k];
    }
    if (k < field.sizeX - 1) {
        count += field.field[i][k + 1];
    }
    if (i > 0 and k > 0) {
        count += field.field[i - 1][k - 1];
    }
    if (i < field.sizeY - 1 and k > 0) {
        count += field.field[i + 1][k - 1];
    }
    if (i < field.sizeY - 1 and k < field.sizeX - 1) {
        count += field.field[i + 1][k + 1];
    }
    if (i > 0 and k < field.sizeX - 1) {
        count += field.field[i - 1][k + 1];
    }
    return count;
}

std::vector<std::pair<int, int>> Game::Logic::change_state(Game::Field_t& field)
{
    std::vector<std::pair<int, int>> changed_cage;
    for (int i = 0; i < field.sizeY; i++) {
        if (i < field.sizeX - 2) {
            int tmp_sum = ((i >= 1) ? config->live_cell_sum[i - 1] : 0) + config->live_cell_sum[i]
                    + config->live_cell_sum[i + 1];
            if (tmp_sum == 0) {
                continue;
            }
        }
        for (int k = 0; k < field.sizeX; k++) {
            std::pair<int, int> cur_coord;
            if (field.field[i][k]
                and !(counting_live_cells(field, i, k) == 2
                      or counting_live_cells(field, i, k) == 3)) {
                cur_coord.first = i;
                cur_coord.second = k;
                changed_cage.push_back(cur_coord);
            } else if (!field.field[i][k] and counting_live_cells(field, i, k) == 3) {
                cur_coord.first = i;
                cur_coord.second = k;
                changed_cage.push_back(cur_coord);
            }
        }
    }
    for (int i = 0; i < changed_cage.size(); i++) {
        field.field[changed_cage[i].first][changed_cage[i].second]
                = !field.field[changed_cage[i].first][changed_cage[i].second];
        if (field.field[changed_cage[i].first][changed_cage[i].second]) {
            config->live_cell_sum[changed_cage[i].first]++;
        } else {
            config->live_cell_sum[changed_cage[i].first]--;
        }
    }
    return changed_cage;
}
