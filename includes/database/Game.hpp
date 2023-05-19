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
    Field_t field;

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

		void print_squard(bool is_live, int coordX, int coordY) {
				sf::RectangleShape cell(sf::Vector2f(20, 20));
				cell.setPosition(sf::Vector2f(coordX*20+100, coordY*20+100));
				cell.setFillColor((is_live) ? sf::Color::White : sf::Color::Black);
				cell.setOutlineThickness(1);
				cell.setOutlineColor(sf::Color::White);
				window_p->draw(cell);
		}

    void display()
    {
        for (int i = 0; i < field.sizeX; i++) {
					for (int k = 0; k < field.sizeY; k++) {
						print_squard(field.field[i][k], i, k);
					}
				}
				window_p->display();
    }

private:
    int windowX;
    int windowY;
    sf::RenderWindow* window_p;
};
};

#endif
