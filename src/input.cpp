#include <iostream>
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

void Game::Input::allocate_memory_for_field(Game::Field_t& map)
{
    map.field = new bool*[map.sizeY];
    for (int i = 0; i < map.sizeY; i++) {
        map.field[i] = new bool[map.sizeX];
        for (int k = 0; k < map.sizeX; k++) {
            map.field[i][k] = 0;
        }
    }
}

void Game::Game_window::setInputMode()
{
    config->input_mode = true;
    config->game_mode = false;
}

void Game::Input::process_mouse_click()
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*config->window_p);
    // std::cout << mouse_pos.x << ' ' << mouse_pos.y
    //           << "startX = " << config->windowX - config->offsetX
    //           << "startY = " << config->windowY - config->offsetY << '\n';
    int cellX = (mouse_pos.x - (config->windowX - (config->windowX - config->offsetX)))
            / config->size_cell;
    int cellY = (mouse_pos.y - (config->windowY - (config->windowY - config->offsetY)))
            / config->size_cell;
    if (cellX == last_clickX and cellY == last_clickY) {
        return;
    }
    if (cellX >= config->field.sizeX or cellY >= config->field.sizeY or cellX < 0 or cellY < 0) {
        return;
    }
    last_clickX = cellX;
    last_clickY = cellY;
    // std::cout << "cellX = " << cellX << " cellY = " << cellY << '\n';
    config->field.field[cellY][cellX] = !config->field.field[cellY][cellX];
    if (config->field.field[cellY][cellX]) {
        config->live_cell_sum[cellY]++;
    } else {
        config->live_cell_sum[cellY]--;
    }
    print_squard(config->field.field[cellY][cellX], cellY, cellX, config->offsetX, config->offsetY);
}

void Game::Input::get_map_from_user(Game::Game_window& game_window)
{
    game_window.get_config()->field.sizeX = 100;
    game_window.get_config()->field.sizeY = 87;
    game_window.calculate_cell_size();
    allocate_memory_for_field(game_window.get_config()->field);
    game_window.setInputMode();
    game_window.display();

    bool resized = false;

    while (config->window_p->isOpen()) {
        sf::Event event;
        while (config->window_p->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                config->window_p->close();
            if (event.type == sf::Event::KeyPressed) {
                if (process_the_key(event)) {
                    return;
                };
            }
            if (!resized and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                process_mouse_click();
            }
            int width, height;
            if (event.type == sf::Event::Resized) {
                resized = true;
                height = event.size.height;
                width = event.size.width;
                config->window_p->clear();

            } else if (resized) {
                resized = false;
                std::cout << "start\n";
                game_window.resized(width, height);

                config->window_p->clear();
                game_window.display();
                std::cout << "finish\n";
            }
        }

        config->window_p->display();
    }
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
}

int Game::Input::input_keyboard(sf::Event& event)
{
    std::pair<int, int> change_cage;
    switch (event.key.code) {
    case sf::Keyboard::W:
    case sf::Keyboard::Up:
        print_squard(config->field.field[posY][posX], posY, posX, config->offsetX, config->offsetY);
        posY = (config->field.sizeY + ((posY - 1) % config->field.sizeY)) % config->field.sizeY;
        user_choise();

        break;
    case sf::Keyboard::A:
    case sf::Keyboard::Left:

        print_squard(config->field.field[posY][posX], posY, posX, config->offsetX, config->offsetY);

        posX = (config->field.sizeX + ((posX - 1) % config->field.sizeX)) % config->field.sizeX;
        user_choise();
        break;
    case sf::Keyboard::S:
    case sf::Keyboard::Down:

        print_squard(config->field.field[posY][posX], posY, posX, config->offsetX, config->offsetY);

        posY = (config->field.sizeY + ((posY + 1) % config->field.sizeY)) % config->field.sizeY;

        user_choise();
        break;
    case sf::Keyboard::D:
    case sf::Keyboard::Right:

        print_squard(config->field.field[posY][posX], posY, posX, config->offsetX, config->offsetY);
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
        print_squard(1, posY, posX, config->offsetX, config->offsetY);
    case sf::Keyboard::Space:
        return 1;
    default:
        break;
    }
    return 0;
}

int Game::Input::process_the_key(sf::Event& event)
{
    if (config->input_mode) {
        if (input_keyboard(event)) {
            return 1;
        };
    } else if (config->game_mode) {
    }
    return 0;
}

// bool Game::Input::define_the_key(sf::Event& event)
// {
//     for (int i = 0; i < key_count; i++)
//         if (event.key.code == keyboard[i])
//             return true;
//     return false;
// }
