#include <SFML/Graphics.hpp>
#include <ctest.h>

#include <Game.hpp>

Game::Backend* test_game;
void create_field()
{
    Game::window_config* config = new Game::window_config;
    config->field.sizeX = 9;
    config->field.sizeY = 9;
    config->live_cell_sum = new int[9];
    config->field.field = new bool*[9];
    for (int i = 0; i < 9; i++) {
        config->field.field[i] = new bool[9];
    }
    test_game = new Game::Backend{config};
    bool map[9][9]
            = {{0, 1, 0, 0, 0, 0, 0, 0, 0},
               {1, 0, 1, 0, 0, 0, 0, 0, 0},
               {1, 0, 1, 0, 0, 0, 0, 0, 0},
               {1, 0, 1, 0, 0, 0, 0, 0, 0},
               {0, 1, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 1, 1, 1, 0},
               {0, 0, 0, 0, 0, 1, 0, 1, 0},
               {0, 0, 0, 0, 0, 1, 1, 1, 0}};
    for (int i = 0; i < test_game->config->field.sizeY; i++) {
        for (int k = 0; k < test_game->config->field.sizeX; k++) {
            test_game->config->field.field[i][k] = map[i][k];
        }
    }
}

void calc_sum(Game::window_config* config)
{
    for (int i = 0; i < config->field.sizeY; i++) {
        config->live_cell_sum[i] = 0;
        for (int k = 0; k < config->field.sizeX; k++) {
            config->live_cell_sum[i] += config->field.field[i][k];
        }
    }
}

CTEST(logic, createmap)
{
    create_field();
}

CTEST(logic, countlivecell)
{
    ASSERT_EQUAL(2, test_game->counting_live_cells(test_game->config->field, 2, 2));
    ASSERT_EQUAL(8, test_game->counting_live_cells(test_game->config->field, 7, 6));
    ASSERT_EQUAL(2, test_game->counting_live_cells(test_game->config->field, 5, 5));
    ASSERT_EQUAL(0, test_game->counting_live_cells(test_game->config->field, 0, 8));
    ASSERT_EQUAL(2, test_game->counting_live_cells(test_game->config->field, 0, 0));
}

CTEST(logic, changemap)
{
    int res[9][9]
            = {{0, 1, 0, 0, 0, 0, 0, 0, 0},
               {1, 0, 1, 0, 0, 0, 0, 0, 0},
               {1, 0, 1, 1, 0, 0, 0, 0, 0},
               {1, 0, 1, 0, 0, 0, 0, 0, 0},
               {0, 1, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 1, 0, 0},
               {0, 0, 0, 0, 0, 1, 0, 1, 0},
               {0, 0, 0, 0, 1, 0, 0, 0, 1},
               {0, 0, 0, 0, 0, 1, 0, 1, 0}};

    calc_sum(test_game->config);
    test_game->change_state(test_game->config->field);

    for (int i = 0; i < 9; i++) {
        for (int k = 0; k < 9; k++) {
            ASSERT_EQUAL(res[i][k], test_game->config->field.field[i][k]);
        }
    }
}