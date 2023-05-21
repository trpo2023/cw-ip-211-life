#include <SFML/Graphics.hpp>
#include <string>
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
    bool input_mode;
    bool game_mode;
    bool is_resized = false;
    float offsetX;
    float offsetY;
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
    void clear();

    Input(window_config*& config_gl)
    {
        config = config_gl;
    }

    void display(std::vector<std::pair<int, int>> mas)
    {
        for (int i = 0; i < mas.size(); i++) {
            print_squard(
                    config->field.field[mas[i].first][mas[i].second], mas[i].first, mas[i].second);
        }
        config->window_p->display();
    }
    void print_squard(bool is_live, int coordY, int coordX);

    void resized(int width, int height)
    {
        sf::FloatRect visiableArea(0, 0, width, height);
        config->window_p->setView(sf::View(visiableArea));
        config->windowX = width;
        config->windowY = height;
        calculate_cell_size();
        calc_offsets();
    }

    void display()
    {
        for (int i = 0; i < config->field.sizeY; i++) {
            for (int k = 0; k < config->field.sizeX; k++) {
                print_squard(config->field.field[i][k], i, k);
            }
        }
        config->window_p->display();
    }

    void calculate_cell_size()
    {
        float X = (config->windowX - config->windowX * config->margin * 2.) / config->field.sizeX;
        float Y = (config->windowY - config->windowY * config->margin * 2.) / config->field.sizeY;
        config->size_cell = (X < Y) ? X : Y;
        calc_offsets();
    }
    void calc_offsets()
    {
        config->offsetX = (config->windowX - config->field.sizeX * config->size_cell) / 2.;
        config->offsetY = (config->windowY - config->field.sizeY * config->size_cell) / 2.;
    }

    void allocate_memory_for_field(Game::Field_t& map);
    int input_keyboard(sf::Event&);
    void process_mouse_click();

private:
    void user_choise();
    int get_int(std::string& input, int& i);

    int last_clickX = -1;
    int last_clickY = -1;
    int posX = 0;
    int posY = 0;
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
        config->field.sizeX = 50;
        config->field.sizeY = 50;
        config->input_mode = true;
        config->game_mode = false;

        static Input input{config};
        static Logic logic{config};

        input_p = &input;
        logic_p = &logic;

        input_p->calculate_cell_size();
        setInputMode();
        input_p->allocate_memory_for_field(config->field);
        input_p->display();
    }

    void display()
    {
        input_p->display();
    }
    sf::RenderWindow* get_window()
    {
        return config->window_p;
    }
    void setGameMode()
    {
        config->game_mode = true;
        config->input_mode = false;
    }

    window_config*& get_config()
    {
        return config;
    }

    void game(sf::Event& event);
    void setInputMode();

private:
    void resized(sf::Event& event);

    window_config* config;
};
};

#endif
