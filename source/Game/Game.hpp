#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include <iomanip>
#include "Rotation.hpp"
#include "BackgroundBoard/BackgroundBoard.hpp"
#include "Player/Player.hpp"
#include "World/World.hpp"
#include "World/Components/Inverter/Inverter.hpp"
#include "World/Components/Blotter/Blotter.hpp"
#include "World/Components/Peg/Peg.hpp"


using namespace std;

class Interaction;

class Game
{
        friend Interaction;
    private:
        sf::String windowLabel = "The Window";
        sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 600), windowLabel, sf::Style::Default, sf::ContextSettings(0, 0, 4));
        sf::Clock deltaTimeClock;
        sf::Font font;
        BasicComponent shadowComponent[Component::AMOUNT];
        Player player;
        BackgroundBoard backgroundBoard = BackgroundBoard(window.getSize(), player.getScale());
        World world;
        Interaction* interaction; // initialization is in constructor
        float fps = 0;
        
        bool isMouseInsideWindow(sf::Vector2i mousePosition);
        sf::Vector2f mouseToCellPosition(sf::Vector2i mousePosition);
        std::string getDrawText();
        void handleMousePress();
    public:
        Game();
        bool isOpen();
        bool pollEvent(sf::Event& event);
        void handleEvent(sf::Event& event);
        void update();
        void draw();
};

#include "Interaction/Interaction.hpp"

#endif //GAME_GAME_HPP
