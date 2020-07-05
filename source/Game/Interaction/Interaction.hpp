#ifndef GAME_INTERACTION_HPP
#define GAME_INTERACTION_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../World/Components/BasicComponent.hpp"
#include "../PlayerState.hpp"
#include "../World/Components/Switch/Switch.hpp"

class Game;

class Interaction {
    private:
        sf::Vector2f connectionPositionDraw;
        sf::Vector2u connectionPosition;
        BasicComponent* connectionComponent = nullptr;
        
        bool handleConnectionTry(Game& game);
        static bool handleNewComponentTry(Game& game);
        static bool handleRemoveComponentTry(Game& game);
        static bool handleInteractables(Game& game);
    public:
        static bool isConnecting(Game& game);
        sf::Vector2f getStartConnectionPoint();
        static void drawShadow(Game& game);
        bool handleEvent(Game& game, sf::Event& event);
        void update(Game& game);
};

#include "../Game.hpp"

#endif //GAME_INTERACTION_HPP
