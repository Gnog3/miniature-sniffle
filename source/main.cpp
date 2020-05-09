#include <iostream>
#include "Game/Game.hpp"
#include <SFML/Window/Event.hpp>

using namespace std;

int main()
{
    // Game
    {
        if (sizeof(nullptr) == 8)
        {
            std::cout << "x64" << std::endl;
        }
        else if (sizeof(nullptr) == 4)
        {
            std::cout << "x32" << std::endl;
        }
    } // Detecting bitness
    
    Game game;
    
    while (game.isOpen())
    {
        sf::Event event{};
        while (game.pollEvent(event))
        {
            game.handleEvent(event);
        }
        game.update();
        game.draw();
    }
}