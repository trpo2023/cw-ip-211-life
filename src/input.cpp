#include <chrono>
#include <map>
#include <string>
#include <vector>

#include <Game.hpp>

int Game::Input::get_int(std::string& input, int& i)
{
    std::string digit;
    for (; i < input.size() && input[i] != ','; i++) {
        if (input[i] == ' ')
            continue;
        digit.push_back(input[i]);
    }
    i++;
    return stod(digit);
}

void Game::Input::print_squard(bool is_live, int coordY, int coordX)
{
    float offsetX = config->offsetX;
    float offsetY = config->offsetY;
    sf::RectangleShape cell(sf::Vector2f(config->size_cell, config->size_cell));
    // cell.setScale(sf::Vector2f(0, 0));
    cell.setPosition(sf::Vector2f(
            coordX * config->size_cell + offsetX, coordY * config->size_cell + offsetY));
    cell.setFillColor((is_live) ? sf::Color::White : sf::Color::Black);
    cell.setOutlineThickness(1);
    cell.setOutlineColor(sf::Color::White);
    config->window_p->draw(cell);
}

void Game::Input::allocate_memory_for_field(Game::Field_t& map)
{
    map.field = new bool*[map.sizeY];
    config->live_cell_sum = new int[map.sizeY];
    for (int i = 0; i < map.sizeY; i++) {
        map.field[i] = new bool[map.sizeX];
        config->live_cell_sum[i] = 0;
        for (int k = 0; k < map.sizeX; k++) {
            map.field[i][k] = 0;
        }
    }
}

void Game::Game_window::setInputMode()
{
    config->input_mode = true;
    config->game_mode = false;
    config->settings_mode = false;
}

void Game::Input::process_mouse_click()
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*config->window_p);
    int cellX = (mouse_pos.x - config->offsetX) / config->size_cell;
    int cellY = (mouse_pos.y - config->offsetY) / config->size_cell;
    if (cellX == last_clickX and cellY == last_clickY) {
        return;
    }
    if (cellX >= config->field.sizeX or cellY >= config->field.sizeY or cellX < 0 or cellY < 0) {
        return;
    }

    last_clickX = cellX;
    last_clickY = cellY;
    config->field.field[cellY][cellX] = !config->field.field[cellY][cellX];
    if (config->field.field[cellY][cellX]) {
        config->live_cell_sum[cellY]++;
    } else {
        config->live_cell_sum[cellY]--;
    }
    print_squard(config->field.field[cellY][cellX], cellY, cellX);
    config->window_p->display();
}

void Game::Input::user_choise()
{
    sf::RectangleShape cell(sf::Vector2f(config->size_cell, config->size_cell));
    cell.setPosition(sf::Vector2f(
            posX * config->size_cell + config->offsetX,
            posY * config->size_cell + config->offsetY));
    cell.setFillColor(sf::Color::Magenta);
    cell.setOutlineThickness(1);
    cell.setOutlineColor(sf::Color::White);
    config->window_p->draw(cell);
    config->window_p->display();
}

void Game::Input::clear()
{
    for (int i = 0; i < config->field.sizeY; i++) {
        config->live_cell_sum[i] = 0;
        for (int k = 0; k < config->field.sizeX; k++) {
            config->field.field[i][k] = false;
        }
    }
    display();
}

void Game::Input::input_keyboard(sf::Event& event)
{
    std::pair<int, int> change_cage;
    switch (event.key.code) {
    case sf::Keyboard::W:
    case sf::Keyboard::Up:
        print_squard(config->field.field[posY][posX], posY, posX);
        posY = (config->field.sizeY + ((posY - 1) % config->field.sizeY)) % config->field.sizeY;
        user_choise();

        break;
    case sf::Keyboard::A:
    case sf::Keyboard::Left:

        print_squard(config->field.field[posY][posX], posY, posX);

        posX = (config->field.sizeX + ((posX - 1) % config->field.sizeX)) % config->field.sizeX;
        user_choise();
        break;
    case sf::Keyboard::S:
    case sf::Keyboard::Down:
        print_squard(config->field.field[posY][posX], posY, posX);
        posY = (config->field.sizeY + ((posY + 1) % config->field.sizeY)) % config->field.sizeY;
        user_choise();
        break;
    case sf::Keyboard::D:
    case sf::Keyboard::Right:
        print_squard(config->field.field[posY][posX], posY, posX);
        posX = (config->field.sizeX + ((posX + 1) % config->field.sizeX)) % config->field.sizeX;
        user_choise();
        break;
    case sf::Keyboard::Enter:
        config->field.field[posY][posX] = !config->field.field[posY][posX];
        if (config->field.field[posY][posX]) {
            config->live_cell_sum[posY]++;
        } else {
            config->live_cell_sum[posY]--;
        }
        break;
    default:
        break;
    }
    return;
}

void Game::Game_window::setSettingMode()
{
    config->settings_mode = true;
    config->game_mode = false;
    config->input_mode = false;
}

void Game::Game_window::configurate_settings()
{
    config->settings.x = config->field.sizeX;
    config->settings.y = config->field.sizeY;
    config->settings.windowX = config->windowX;
    config->settings.windowY = config->windowY;
    config->settings.offsetX = config->settings.windowX * config->margin;
    config->settings.offsetY = config->settings.windowY * config->margin;
    config->window_settings = new sf::RenderWindow(
            sf::VideoMode(config->settings.windowX, config->settings.windowY), "settings");
    config->window_settings->setPosition(sf::Vector2i(0, 0));
    config->window_settings->setKeyRepeatEnabled(false);

    input_p->draw_settings();

    setSettingMode();
}

void Game::Input::draw_property(sf::Color color, int index)
{
    static float offsetX = config->settings.offsetX;
    static float offsetY = config->settings.offsetY;
    static int margin = 100;
    static sf::RectangleShape choise(sf::Vector2f(config->settings.windowX - offsetX, margin));
    static sf::Text property_text;
    static sf::Text property_value;
    static sf::Font font;

    install_font(property_text, 20, "../font/second_font.ttf");
    install_font(property_value, 20, "../font/second_font.ttf");
    choise.setPosition(sf::Vector2f(offsetX, offsetY + margin * index));
    choise.setFillColor(color);
    config->window_settings->draw(choise);

    property_text.setString(config->settings.property[index]);
    property_text.setPosition(sf::Vector2f(offsetX, offsetY + margin * index));
    config->window_settings->draw(property_text);
    property_value.setPosition(
            sf::Vector2f(config->settings.windowX - offsetX, offsetY + margin * index));
    property_value.setString(std::to_string(*config->settings.order[index]));
    config->window_settings->draw(property_value);
    config->window_settings->display();
}

void Game::Input::install_font(sf::Text& text, int char_size, std::string font_path)
{
    static sf::Font font;
    font.loadFromFile(font_path);
    text.setFont(font);
    text.setCharacterSize(char_size);
}

void Game::Input::draw_settings()
{
    sf::Text property_text;
    sf::Text property_value;
    install_font(property_text, 20, "../font/second_font.ttf");
    install_font(property_value, 20, "../font/second_font.ttf");
    float offsetX = config->settings.offsetX;
    float offsetY = config->settings.offsetY;

    int margin = 100;

    for (int i = 0; i < config->settings.property.size() - 1; i++) {
        if (config->settings.cur_choise == i) {
            draw_property(sf::Color::Blue, i);
        } else {
            draw_property(sf::Color::Black, i);
        }
        int porperty_size = config->settings.property.size();
        property_text.setString(config->settings.property[porperty_size - 1]);
        property_text.setPosition(sf::Vector2f(
                config->settings.offsetX, config->settings.offsetY + 100 * (porperty_size - 1)));
        property_text.setCharacterSize(
                (config->settings.windowX / config->settings.property[porperty_size - 1].size())
                * 2);
        config->window_settings->draw(property_text);

        config->window_settings->display();
    }
}

void Game::Input::relocate()
{
    config->input_mode = true;
    config->settings_mode = false;
    calculate_cell_size();
    calc_offsets();
    if (config->settings.is_changed)
        allocate_memory_for_field(config->field);
    config->window_p->clear();
    display();
}

void Game::Input::control_settings(sf::Event& event)
{
    std::string new_value;
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::M:
            relocate();

            config->window_settings->close();
            config->window_p->display();
            return;
        case sf::Keyboard::Up:
            draw_property(sf::Color::Black, config->settings.cur_choise);

            config->settings.cur_choise
                    = ((config->settings.cur_choise - 1 < 0) ? config->settings.property.size() - 2
                                                             : (config->settings.cur_choise - 1)
                                       % (config->settings.property.size() - 1));
            draw_property(sf::Color::Blue, config->settings.cur_choise);
            break;
        case sf::Keyboard::Down:
            draw_property(sf::Color::Black, config->settings.cur_choise);

            config->settings.cur_choise
                    = (config->settings.cur_choise + 1) % (config->settings.property.size() - 1);
            draw_property(sf::Color::Blue, config->settings.cur_choise);

            break;
        case sf::Keyboard::Enter:
            draw_property(sf::Color::Red, config->settings.cur_choise);

            while (config->window_settings->waitEvent(event)) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        if (*config->settings.order[config->settings.cur_choise] == 0) {
                            continue;
                        }
                        config->settings.is_changed = true;
                        break;
                    }
                    if (event.key.code == sf::Keyboard::BackSpace) {
                        if (new_value.size() > 1) {
                            new_value.pop_back();
                            *config->settings.order[config->settings.cur_choise]
                                    = std::stoi((new_value.c_str()));
                            draw_property(sf::Color::Red, config->settings.cur_choise);

                            continue;
                        } else {
                            if (new_value.size() != 0)
                                new_value.pop_back();
                            *config->settings.order[config->settings.cur_choise] = 0;
                            draw_property(sf::Color::Red, config->settings.cur_choise);
                        }
                    }
                }
                if (event.type == sf::Event::TextEntered) {
                    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        if (new_value.size() < 5 and event.text.unicode >= '0'
                            and event.text.unicode <= '9') {
                            new_value.push_back(event.text.unicode);
                            *config->settings.order[config->settings.cur_choise]
                                    = std::stoi((new_value.c_str()));
                            draw_property(sf::Color::Red, config->settings.cur_choise);
                        }
                    }
                }
            }
            switch (config->settings.cur_choise) {
            case 0:
                config->field.sizeX = std::stoi((new_value.c_str()));
                break;
            case 1:
                config->field.sizeY = std::stoi((new_value.c_str()));
                break;
            case 2:
                config->delay_between_changed_generations = std::stoi((new_value.c_str()));
                break;
            default:
                break;
            }
            *config->settings.order[config->settings.cur_choise] = std::stoi((new_value.c_str()));
            draw_settings();

            break;

        default:
            break;
        }
    }
}

void Game::Game_window::game(sf::Event& event)
{
    if (resized(event)) {
        return;
    }

    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Space:
            if (config->auto_change == true)
                break;
            if (config->input_mode) {
                setGameMode();
            } else {
                setInputMode();
            }
            config->window_p->clear();
            display();
            return;
            break;
        case sf::Keyboard::K:
            input_p->clear();
            break;
        case sf::Keyboard::R:
            config->cur_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                                       std::chrono::system_clock::now().time_since_epoch())
                                       .count();
            config->auto_change = !config->auto_change;
            break;
        case sf::Keyboard::M:
            configurate_settings();

            break;
        default:
            break;
        }
    }
    if (config->game_mode and !config->input_mode and !config->settings_mode) {
        auto time_now = std::chrono::system_clock::now();
        int64_t ms
                = std::chrono::duration_cast<std::chrono::milliseconds>(time_now.time_since_epoch())
                          .count();

        if (config->auto_change) {
            if (config->cur_time + config->delay_between_changed_generations < ms) {
                input_p->display(logic_p->change_state(config->field));
                config->cur_time = ms;
            }
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::O) {
                input_p->display(logic_p->change_state(config->field));
            }
        }
    } else if (!config->game_mode and config->input_mode and !config->settings_mode) {
        if (event.type == sf::Event::KeyPressed) {
            input_p->input_keyboard(event);
            // if (input_p->input_keyboard(event)) {
            //     setGameMode();
            // };
        }
        if (!config->is_resized and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            input_p->process_mouse_click();
        }
    } else if (config->settings_mode and !config->game_mode and !config->input_mode) {
        if (config->window_settings->isOpen()) {
            static sf::Event settings_event;
            while (config->window_settings->pollEvent(settings_event)) {
                if (settings_event.type == sf::Event::Resized) {
                    config->settings.windowX = settings_event.size.width;
                    config->settings.windowY = settings_event.size.height;
                    sf::FloatRect visiableArea(
                            0, 0, config->settings.windowX, config->settings.windowY);
                    config->window_settings->setView(sf::View(visiableArea));
                    input_p->draw_settings();
                }
                if (settings_event.type == sf::Event::Closed)
                    config->window_settings->close();
                input_p->control_settings(settings_event);
            }
        }
    }
}

bool Game::Game_window::resized(sf::Event& event)
{
    static int width, height;
    if (event.type == sf::Event::Resized) {
        config->is_resized = true;
        height = event.size.height;
        width = event.size.width;
        config->window_p->clear();
        config->window_p->display();
        return true;
    } else if (config->is_resized) {
        config->is_resized = false;
        input_p->resized(width, height);
        display();
        return true;
    }
    return false;
}