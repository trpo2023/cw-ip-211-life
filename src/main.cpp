#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include <Game.hpp>

int main()
{
    const int windowX = 1000;
    const int windowY = 1000;
    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "SFML works!");
    Game::Game_window game_window{window, windowX, windowY};

    game_window.get_map_from_user(game_window);

    game_window.display();
    window.setKeyRepeatEnabled(false);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Return) {
                    game_window.display(
                            game_window.change_state(game_window.field));
                }
            }
        }
    }
    return 0;
}