#include <SFML/Graphics.hpp>
#include <iostream>
#ifndef MAP_HPP
#define MAP_HPP

namespace Game {
struct Field_t {
    int sizeX;
    int sizeY;
    bool** field;
};

class Game_window {
public:
    Field_t field;

    Game_window(sf::RenderWindow& window, int x, int y)
    {
        windowX = x;
        windowY = y;
        window_p = &window;
        live_cell_sum = new int[y];
    }

    sf::RenderWindow* get_window()
    {
        return window_p;
    }

    void calculate_cell_size()
    {
        size_cell = (windowX - windowX * margin * 2.) / field.sizeX;
    }

    void print_squard(bool is_live, int coordX, int coordY, int offset)
    {
        // std::cout << size_cell << '\n';
        sf::RectangleShape cell(sf::Vector2f(size_cell, size_cell));
        cell.setPosition(sf::Vector2f(
                coordX * size_cell + offset, coordY * size_cell + offset));
        cell.setFillColor((is_live) ? sf::Color::White : sf::Color::Black);
        cell.setOutlineThickness(1);
        cell.setOutlineColor(sf::Color::White);
        window_p->draw(cell);
    }

    void display(std::vector<std::pair<int, int>> mas)
    {
        for (int i = 0; i < mas.size(); i++) {
            print_squard(
                    field.field[mas[i].first][mas[i].second],
                    mas[i].first,
                    mas[i].second,
                    (windowX - field.sizeX * size_cell) / 2);
        }
        // for (int i = 0; i < field.sizeX; i++) {
        //     for (int k = 0; k < field.sizeY; k++) {
        //         print_squard(
        //                 field.field[i][k],
        //                 i,
        //                 k,
        //                 (windowX - field.sizeX * size_cell) / 2);
        //     }
        // }
        window_p->display();
    }
    void display()
    {
        for (int i = 0; i < field.sizeX; i++) {
            for (int k = 0; k < field.sizeY; k++) {
                print_squard(
                        field.field[i][k],
                        i,
                        k,
                        (windowX - field.sizeX * size_cell) / 2);
            }
        }
        window_p->display();
    }
    std::vector<std::pair<int, int>> change_state(Game::Field_t& field);

    int get_int(std::string& input, int& i);

    void allocate_memory_for_field(Game::Field_t& map);

    void get_map_from_user(Game::Game_window& game_window);
    template <typename T1, typename T2>
    int counting_live_cells(Game::Field_t& field, T1 i, T2 k);

private:
    int windowX;
    int windowY;
    float size_cell;
    double margin = 0.1;
    sf::RenderWindow* window_p;
    int* live_cell_sum;
};
};

#endif
