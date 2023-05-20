#include <SFML/Graphics.hpp>
#include <iostream>
#ifndef MAP_HPP
#define MAP_HPP

namespace Game {
class Game_window;

struct Field_t {
    int sizeX;
    int sizeY;
    bool** field;
};
class window_config {
public:
    int windowX;
    int windowY;
    float size_cell;
    double margin = 0.1;
    sf::RenderWindow* window_p;
    int* live_cell_sum;
    Field_t field;
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

    void resized(unsigned int newX, unsigned int newY)
    {
        config->windowX = newX;
        config->windowY = newY;
        calculate_cell_size();
    }

    sf::RenderWindow* get_window()
    {
        return config->window_p;
    }

    void calculate_cell_size()
    {
        float X = (config->windowX - config->windowX * config->margin * 2.)
                / get_config()->field.sizeX;
        float Y = (config->windowY - config->windowY * config->margin * 2.)
                / get_config()->field.sizeY;
        std::cout << "X = " << X << "\nY = " << Y << " windowY = " << config->windowY
                  << " windowX = " << config->windowX << '\n';
        config->size_cell = (X < Y) ? X : Y;
    }

    window_config*& get_config()
    {
        return config;
    }

    void print_squard(bool is_live, int coordY, int coordX, float offsetX, float offsetY)
    {
        sf::RectangleShape cell(sf::Vector2f(config->size_cell, config->size_cell));
        // cell.setScale(sf::Vector2f(0, 0));
        cell.setPosition(sf::Vector2f(
                coordX * config->size_cell + offsetX, coordY * config->size_cell + offsetY));
        cell.setFillColor((is_live) ? sf::Color::White : sf::Color::Black);
        cell.setOutlineThickness(1);
        cell.setOutlineColor(sf::Color::White);
        config->window_p->draw(cell);
    }

    void display(std::vector<std::pair<int, int>> mas)
    {
        for (int i = 0; i < mas.size(); i++) {
            print_squard(
                    get_config()->field.field[mas[i].first][mas[i].second],
                    mas[i].first,
                    mas[i].second,
                    (config->windowX - get_config()->field.sizeX * config->size_cell) / 2.,
                    (config->windowY - get_config()->field.sizeY * config->size_cell) / 2.);
        }
        config->window_p->display();
    }
    void display()
    {
        std::cout << config->window_p->getPosition().x << ' ' << config->window_p->getPosition().x
                  << '\n';
        for (int i = 0; i < get_config()->field.sizeY; i++) {
            for (int k = 0; k < get_config()->field.sizeX; k++) {
                print_squard(
                        get_config()->field.field[i][k],
                        i,
                        k,
                        (config->windowX - get_config()->field.sizeX * config->size_cell) / 2.,
                        (config->windowY - get_config()->field.sizeY * config->size_cell) / 2.);
            }
        }
        config->window_p->display();
    }

private:
    window_config* config;
};
};

#endif
