#include <SFML/Graphics.hpp>
#include <ctest.h>

#include <Game.hpp>

Game::Game_window* test_game;
void create_field()
{
    test_game->field.sizeX = 9;
    test_game->field.sizeY = 9;
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
    for (int i = 0; i < test_game->field.sizeY; i++) {
        for (int k = 0; k < test_game->field.sizeX; k++) {
            test_game->field.field[i][k] = map[i][k];
        }
    }
}

CTEST(logic, createmap)
{
    create_field();
}

CTEST(logic, countlivecell)
{
    ASSERT_EQUAL(2, test_game->counting_live_cells(test_game->field, 2, 2));
    ASSERT_EQUAL(8, test_game->counting_live_cells(test_game->field, 7, 6));
    ASSERT_EQUAL(2, test_game->counting_live_cells(test_game->field, 5, 5));
    ASSERT_EQUAL(0, test_game->counting_live_cells(test_game->field, 0, 8));
    ASSERT_EQUAL(2, test_game->counting_live_cells(test_game->field, 0, 0));
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
    sf::RenderWindow window(sf::VideoMode(100, 100), "SFML works!");

    test_game = new Game::Game_window{window, 0, 0};
    test_game->change_state(test_game->field);
    for (int i = 0; i < 9; i++) {
        for (int k = 0; k < 9; k++) {
            ASSERT_EQUAL(res[i][k], test_game->field.field[i][k]);
        }
    }
}