#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <limits>
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

struct Settings {
    int windowX;
    int windowY;
    int x;
    int y;
    float offsetX;
    float offsetY;
    int delay_between_changed_generations = 1000;
    int* order[3] = {&x, &y, &delay_between_changed_generations};
    float margin = 0.1;
    std::vector<std::string> property
            = {"size map X",
               "size map Y",
               "delay",
               "enter - to chose property and then enter to accept property\ndown, Up - to "
               "control\nM - to accept changes"};
    int cur_choise = 0;
};
class window_config {
public:
    int windowX;
    int windowY;
    float size_cell;
    double margin = 0.1;
    sf::RenderWindow* window_p;
    sf::RenderWindow* window_settings;
    int* live_cell_sum;
    Field_t field;
    Settings settings;
    bool input_mode;
    bool game_mode;
    bool settings_mode;
    bool is_resized = false;
    float offsetX;
    float offsetY;
    bool auto_change = false;
    int delay_between_changed_generations = 1000;
    int64_t cur_time;
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
    void draw_settings();

    void resized(int width, int height)
    {
        sf::FloatRect visiableArea(0, 0, width, height);
        config->window_p->setView(sf::View(visiableArea));
        config->windowX = width;
        config->windowY = height;
        calculate_cell_size();
        calc_offsets();
    }

    void print_manual()
    {
        int width = config->windowX;
        int startX = 0;
        float font_coof = 2;
        int y = config->windowY - config->offsetY / 2;
        std::vector<std::string> cur_manual_text;

        if (config->input_mode and !config->game_mode) {
            cur_manual_text = manual[0];
        } else {
            cur_manual_text = manual[1];
        }

        int mess_number = cur_manual_text.size();
        int unit = width / mess_number;
        int max_message_size = 0;

        for (int i = 0; i < mess_number; i++) {
            if (cur_manual_text[i].size() > max_message_size)
                max_message_size = cur_manual_text[i].size();
        }
        float font_size = (unit / static_cast<float>(max_message_size)) * font_coof;
        if (font_size > 20) {
            font_size = 20;
        }
        sf::Text manual_text;
        sf::Font font;
        font.loadFromFile("../font/Ubuntu-Regular.ttf");
        manual_text.setFont(font);
        manual_text.setCharacterSize(font_size);
        config->window_p->draw(manual_text);
        config->window_p->display();
        for (int i = 0; i < mess_number; i++) {
            manual_text.setString(cur_manual_text[i]);
            manual_text.setPosition(sf::Vector2f(unit * i, y));
            config->window_p->draw(manual_text);
        }
    }

    void display()
    {
        for (int i = 0; i < config->field.sizeY; i++) {
            for (int k = 0; k < config->field.sizeX; k++) {
                print_squard(config->field.field[i][k], i, k);
            }
        }
        print_manual();
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
    void input_keyboard(sf::Event&);
    void control_settings(sf::Event&);
    void user_choise_settings(sf::Color);
    void relocate();

    void process_mouse_click();

private:
    static const int manual_size = 2;
    std::vector<std::vector<std::string>> manual
            = {{"Spase - input/game",
                "w, a, s, d - controlling",
                "enter - select cell",
                "LMB - change cell state",
                "k - clear map",
                "M - open settings"},
               {"Spase - input/game",
                "o - change generation",
                "r - auto/manual",
                "k = clear map",
                "M - open settings"}};
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
        config->window_p->setPosition(sf::Vector2i(0, 0));

        config->live_cell_sum = new int[y];
        config->field.sizeX = 50;
        config->field.sizeY = 50;
        config->input_mode = true;
        config->game_mode = false;
        config->settings_mode = false;

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
        config->settings_mode = false;
    }

    window_config*& get_config()
    {
        return config;
    }

    void game(sf::Event& event);
    void setInputMode();

private:
    void configurate_settings();
    void setSettingMode();
    bool resized(sf::Event& event);

    window_config* config;
};
};

#endif
