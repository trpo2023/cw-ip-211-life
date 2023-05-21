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

    // game_window.input_p->get_map_from_user();

    // game_window.display();
    window.setKeyRepeatEnabled(false);
    bool resized = false;
		game_window.display();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
						game_window.game(event);
        }
        window.display();
    }
    return 0;
}