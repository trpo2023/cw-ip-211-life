#include <SFML/Graphics.hpp>
#include <string>

#include <Game.hpp>

int main()
{
    const int windowX = 1000;
    const int windowY = 1000;
    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "SFML works!");
    Game::Game_window game_window{window, windowX, windowY};

    window.setKeyRepeatEnabled(false);

    while (window.isOpen()) {
        sf::Event event;
        do {
            if (event.type == sf::Event::Closed)
                window.close();
            game_window.game(event);
        } while (window.pollEvent(event));

        window.display();
    }
    return 0;
}