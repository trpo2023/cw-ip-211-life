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

    game_window.input_p->get_map_from_user(game_window);

    game_window.display();
    window.setKeyRepeatEnabled(false);
    bool resized = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Return) {
                    game_window.input_p->display(
                            game_window.logic_p->change_state(game_window.get_config()->field));
                } else {
                    game_window.input_p->process_the_key(event);
                }
            }
            int width, height;
            if (event.type == sf::Event::Resized) {
                resized = true;
                height = event.size.height;
                width = event.size.width;
                window.clear();
                window.hasFocus();

            } else if (resized) {
                resized = false;
                std::cout << "start\n";
                game_window.resized(width, height);

                window.clear();
                game_window.display();
                std::cout << "finish\n";
            }
        }
        window.display();
    }
    return 0;
}