#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <iostream>
using namespace std;
class Player
{
    private:
        sf::Vector2f position = sf::Vector2f(0, 0);
        sf::Vector2i lastMousePosition;
        uint8_t scale = 8;
        bool dragging;
    public:

        void move(sf::Vector2f offset);

        void startDragging();

        void stopDragging();

        void setScale(uint8_t scale);

        uint8_t getScale() const;

        sf::Vector2f handleMousePosition(sf::Vector2i mousePosition);

        sf::Vector2f getPosition();
};

#endif //GAME_PLAYER_HPP
