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
    game_process(game_window);
    return 0;
}