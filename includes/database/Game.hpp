#include <SFML/Graphics.hpp>
#include <iostream>
#ifndef MAP_HPP
#define MAP_HPP

namespace Game {
class Game_window;

class window_config {
public:
    int windowX;
    int windowY;
    float size_cell;
    double margin = 0.1;
    sf::RenderWindow* window_p;
    int* live_cell_sum;
};

struct Field_t {
    int sizeX;
    int sizeY;
    bool** field;
};

class Logic {
public:
    Logic(window_config*& config_gl)
    {
        config = config_gl;
    }
    template <typename T1, typename T2>
    int counting_live_cells(Game::Field_t& field, T1 i, T2 k);
    std::vector<std::pair<int, int>> change_state(Game::Field_t& field);

private:
    window_config* config;
};

class Input {
public:
    Input(window_config*& config_gl)
    {
        config = config_gl;
    }
    int get_int(std::string& input, int& i);
    void allocate_memory_for_field(Game::Field_t& map);
    void get_map_from_user(Game::Game_window& game_window);

private:
    window_config* config;
};
class Game_window {
public:
    Field_t field;
    Logic* logic_p;
    Input* input_p;
    Game_window(sf::RenderWindow& window, int x, int y)
    {
        config = new window_config();
        config->windowX = x;
        config->windowY = y;
        config->window_p = &window;
        config->live_cell_sum = new int[y];
        static Input input{config};
        static Logic logic{config};

        input_p = &input;
        logic_p = &logic;
    }

    sf::RenderWindow* get_window()
    {
        return config->window_p;
    }

    void calculate_cell_size()
    {
        config->size_cell
                = (config->windowX - config->windowX * config->margin * 2.)
                / field.sizeX;
    }

    void print_squard(bool is_live, int coordX, int coordY, int offset)
    {
        sf::RectangleShape cell(
                sf::Vector2f(config->size_cell, config->size_cell));
        cell.setPosition(sf::Vector2f(
                coordX * config->size_cell + offset,
                coordY * config->size_cell + offset));
        cell.setFillColor((is_live) ? sf::Color::White : sf::Color::Black);
        cell.setOutlineThickness(1);
        cell.setOutlineColor(sf::Color::White);
        config->window_p->draw(cell);
    }

    void display(std::vector<std::pair<int, int>> mas)
    {
        for (int i = 0; i < mas.size(); i++) {
            print_squard(
                    field.field[mas[i].first][mas[i].second],
                    mas[i].first,
                    mas[i].second,
                    (config->windowX - field.sizeX * config->size_cell) / 2);
        }
        config->window_p->display();
    }
    void display()
    {
        for (int i = 0; i < field.sizeX; i++) {
            for (int k = 0; k < field.sizeY; k++) {
                print_squard(
                        field.field[i][k],
                        i,
                        k,
                        (config->windowX - field.sizeX * config->size_cell)
                                / 2);
            }
        }
        config->window_p->display();
    }

private:
    window_config* config;
};
};

#endif
