#ifndef GAME_BACKGROUNDBOARD_HPP
#define GAME_BACKGROUNDBOARD_HPP

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <iostream>
#include <cmath>

using namespace std;

class BackgroundBoard {
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        [[nodiscard]]
        static uint8_t* getColorArray(sf::Color background, sf::Color foreground, uint8_t size, uint8_t thickness);
    public:
        BackgroundBoard(sf::RenderWindow& window);
        void recalculate(sf::RenderWindow& window);
        void draw(sf::RenderWindow* window);
};


#endif //GAME_BACKGROUNDBOARD_HPP
