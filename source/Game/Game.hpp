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
#include "World/Components/ComponentData.hpp"


using namespace std;

class Interaction;
#include "Interaction/Interaction.hpp"
class Game
{
        friend Interaction;
    private:
        sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1280, 720), "sim++", sf::Style::Default, sf::ContextSettings(0, 0, 4));
        sf::Clock deltaTimeClock;
        sf::Clock fpsClock;
        uint32_t fpsCount = 0;
        sf::Font font;
        BasicComponent shadowComponent[Component::AMOUNT];
        Player player;
        BackgroundBoard backgroundBoard = BackgroundBoard(window.getSize(), player.getScale());
        World world;
        Interaction interaction; // initialization is in constructor
        float fps = 0;
        uint32_t ups = 0;
        
        bool isMouseInsideWindow(sf::Vector2i mousePosition);
        sf::Vector2f mouseToCellPosition(sf::Vector2i mousePosition);
        std::string getDrawText();
        void handleMousePress();
    public:
        void jk(sf::Vector2i pos);
        Game();
        bool isOpen();
        bool pollEvent(sf::Event& event);
        void handleEvent(sf::Event& event);
        void update();
        void draw();
};



#endif //GAME_GAME_HPP
