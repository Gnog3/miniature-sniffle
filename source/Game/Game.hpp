#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "BackgroundBoard/BackgroundBoard.hpp"
#include "Player/Player.hpp"
#include "World/World.hpp"

using namespace std;

class Game
{
    private:
        sf::String windowLabel = "The Window";
        sf::Vector2u windowResolution = sf::Vector2u(1600, 900);
        sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(windowResolution.x, windowResolution.y), windowLabel);
        sf::Clock deltaTimeClock;
        sf::Font font;

        Player player;
        BackgroundBoard backgroundBoard = BackgroundBoard(windowResolution, player.getScale());
        World world;

        float fps = 0;

        bool isMouseInsideWindow(sf::Vector2i mousePosition);

        sf::Vector2f mouseToCellPosition(sf::Vector2i mousePosition);

    public:
        Game();

        bool isOpen();

        bool pollEvent(sf::Event &event);

        void handleEvent(sf::Event event);

        void update();

        void draw();
};


#endif //GAME_GAME_HPP
