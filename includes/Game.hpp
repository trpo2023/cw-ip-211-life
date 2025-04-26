#include <SFML/Graphics.hpp>
#ifndef MAP_HPP
#define MAP_HPP

namespace Game {
class Game_window;

struct Field_t {
    int sizeX;
    int sizeY;
    int new_sizeX;
    int new_sizeY;
    bool** field;
};

struct Settings {
    int windowX;
    int windowY;
    int x;
    int y;
    int cur_choise = 0;
    int delay_between_changed_generations = 1000;

    float offsetX;
    float offsetY;
    float margin = 0.1;

    int* order[3] = {&x, &y, &delay_between_changed_generations};
    std::vector<std::string> property
            = {"size map X",
               "size map Y",
               "delay",
               "enter - to chose property and then enter to accept property\ndown, Up - to "
               "control\nM - to accept changes"};
    bool is_changed = false;
};
class window_config {
public:
    int windowX;
    int windowY;
    int delay_between_changed_generations = 1000;
    int64_t cur_time;
    double margin = 0.1;
    float size_cell;
    float offsetX;
    float offsetY;
    sf::RenderWindow* window_p;
    sf::RenderWindow* window_settings;
    int* live_cell_sum;
    Field_t field;
    Settings settings;
    bool input_mode;
    bool game_mode;
    bool settings_mode;
    bool is_resized = false;
    bool auto_change = false;
};

class Backend {
public:
    Backend(window_config*& config_gl)
    {
        config = config_gl;
    }
    template <typename T1, typename T2>
    int counting_live_cells(Game::Field_t& field, T1 i, T2 k);
    std::vector<std::pair<int, int>> change_state(Game::Field_t& field);
    window_config* config;
};

class Frontend {
public:
    void clear();

    Frontend(window_config*& config_gl)
    {
        config = config_gl;
    }

    void print_squard(bool is_live, int coordY, int coordX);
    void print_manual();
    void display(std::vector<std::pair<int, int>> mas);
    void display();

    void resized(int width, int height);
    void calculate_cell_size();
    void calc_offsets();

    void user_choise();
    void input_keyboard(sf::Event&);
    void control_settings(sf::Event&);
    void process_mouse_click();

    void draw_settings();
    void draw_property(sf::Color, int);

    void clear_field();
    void relocate();
    void allocate_memory_for_field(Game::Field_t& map, int, int);
    void install_font(sf::Text&, int, std::string);

private:
    static const int manual_size = 2;
    std::vector<std::vector<std::string>> manual
            = {{"Spase - change to game mode",
                "w, a, s, d - controlling",
                "enter - select cell",
                "LMB - change cell state",
                "k - clear map",
                "M - open settings"},
               {"Spase - change to input mode",
                "o - change generation",
                "r - auto/manual",
                "k = clear map",
                "M - open settings"}};
    int get_int(std::string& input, int& i);

    int last_clickX = -1;
    int last_clickY = -1;
    int posX = 0;
    int posY = 0;
    window_config* config;
};
class Game_window {
public:
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
        config->field.new_sizeX = 50;
        config->field.new_sizeY = 50;
        config->input_mode = true;
        config->game_mode = false;
        config->settings_mode = false;

        static Frontend input{config};
        static Backend logic{config};

        frontend_p = &input;
        backend_p = &logic;

        frontend_p->calculate_cell_size();
        setInputMode();
        frontend_p->allocate_memory_for_field(
                config->field, config->field.sizeY, config->field.sizeX);
        frontend_p->display();
    }

    void display()
    {
        frontend_p->display();
    }
    sf::RenderWindow* get_window()
    {
        return config->window_p;
    }

    window_config*& get_config()
    {
        return config;
    }

    void game(sf::Event& event);

private:
    Backend* backend_p;
    Frontend* frontend_p;
    void configurate_settings();
    void setSettingMode();
    void setInputMode();
    void setGameMode();

    bool resized(sf::Event& event);
    window_config* config;
};
};

#endif
