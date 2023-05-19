#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include <Game.hpp>
#include <input.hpp>
#include <logics.hpp>

int main()
{
    const int windowX = 1000;
    const int windowY = 1000;
    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "SFML works!");
    Game::Game_window game_window{window, windowX, windowY};

    get_map_from_user(game_window);
    game_window.display();

    while (window.isOpen()) {
        window.setKeyRepeatEnabled(false);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Return) {
                    change_state(game_window.field);
                    game_window.display();
                }
            }
        }

        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {

        // }
    }
    return 0;
}