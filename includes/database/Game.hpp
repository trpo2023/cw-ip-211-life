#include <SFML/Graphics.hpp>
#ifndef MAP_HPP
#define MAP_HPP

namespace Game {
struct Field_t {
    int sizeX;
    int sizeY;
    bool** field;
};

class Game_window {
public:
    Game_window(sf::RenderWindow& window, int x, int y)
    {
        windowX = x;
        windowY = y;
        window_p = &window;
    }

    sf::RenderWindow* get_window()
    {
        return window_p;
    }
    Field_t field;

private:
    int windowX;
    int windowY;
    sf::RenderWindow* window_p;
};
};

#endif
