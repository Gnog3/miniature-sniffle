#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <iostream>
#include <cmath>
#include "../Rotation.hpp"
#include "../World/Components/Component.hpp"
#include "../PlayerState.hpp"
using namespace std;
class Player
{
    private:
        sf::Vector2f position = sf::Vector2f(0, 0);
        sf::Vector2i lastMousePosition;
        uint8_t scale = 8;
        bool dragging = false;
        Component selectedComponent = Nothing;
        Rotation selectedRotation = Up;
        PlayerState state = Normal;
    public:
        void move(sf::Vector2f offset);
        void startDragging();
        void stopDragging();
        void setScale(uint8_t scale);
        uint8_t getScale() const;
        sf::Vector2f handleMousePosition(sf::Vector2i mousePosition);
        void setPosition(sf::Vector2f value);
        sf::Vector2f getPosition() const;
        void setComponent(Component component);
        Component getActiveComponent();
        void setRotation(Rotation rotation);
        void rotate();
        static Rotation rotate(Rotation rotation);
        Rotation getRotation();
        void setState(PlayerState state);
        PlayerState getState();
};

#endif //GAME_PLAYER_HPP
