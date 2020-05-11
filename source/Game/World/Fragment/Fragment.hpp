#ifndef GAME_FRAGMENT_HPP
#define GAME_FRAGMENT_HPP

#include <SFML/Graphics.hpp>
#include <cstring>
#include "../../Rotation.hpp"
#include "../Components/BasicComponent.hpp"
#include "../Components/Inverter/Inverter.hpp"
#include "../Components/Blotter/Blotter.hpp"
#include "../Components/Peg/Peg.hpp"
#include "../Components/Component.hpp"


class Fragment
{
    private:
        BasicComponent* componentList;
        uint16_t componentAmount = 0;
        sf::Vector2<uint8_t> position;
    public:
        Fragment(sf::Vector2<uint8_t> position);
        ~Fragment();
        uint16_t getComponentAmount();
        void addComponent(Component component, sf::Vector2u position, Rotation rotation);
        bool removeComponent(sf::Vector2u position);
        BasicComponent* getComponent(sf::Vector2<uint8_t> position);
        BasicComponent* getComponent(uint16_t id);
        void calculateInputs();
        void fullTick();
        void shiftState();
        void drawBody(sf::RenderWindow* window, sf::Vector2f playerPosition, sf::Vector2f chunkPosition, uint8_t scale);
        void drawWires(sf::RenderWindow* window, sf::Vector2f playerPosition, sf::Vector2f chunkPosition, uint8_t scale);
        void drawPegs(sf::RenderWindow* window, sf::Vector2f playerPosition, sf::Vector2f chunkPosition, uint8_t scale);
};


#endif //GAME_FRAGMENT_HPP
