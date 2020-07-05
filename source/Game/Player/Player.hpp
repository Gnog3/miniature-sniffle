#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Rotation.hpp"
#include "../World/Components/Component.hpp"
#include "../PlayerState.hpp"

class Game;

class Player {
    private:
        sf::Vector2i lastMousePosition;
        bool dragging = false;
        Component selectedComponent = Nothing;
        Rotation selectedRotation = Rotation::Up;
        PlayerState state = Normal;
        float zoom = 1.0f;
    public:
        void startDragging();
        void stopDragging();
        void handleMousePosition(sf::RenderWindow& window, sf::Vector2i mousePosition);
        void setComponent(Component component);
        Component getActiveComponent();
        void setZoom(float zoom);
        float getZoom() const;
        void setRotation(Rotation rotation);
        void rotate();
        static Rotation rotate(Rotation rotation);
        Rotation getRotation();
        void setState(PlayerState state);
        PlayerState getState();
};

#include "../Game.hpp"

#endif //GAME_PLAYER_HPP
