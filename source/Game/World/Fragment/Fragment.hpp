#ifndef GAME_FRAGMENT_HPP
#define GAME_FRAGMENT_HPP

#include <SFML/Graphics.hpp>
#include <cstring>
#include "../Components/ComponentData.hpp"
#include "../../Rotation.hpp"
#include "../Components/BasicComponent.hpp"
#include "../Components/Inverter/Inverter.hpp"
#include "../Components/Blotter/Blotter.hpp"
#include "../Components/Peg/Peg.hpp"
#include "../Components/Switch/Switch.hpp"
#include "../Components/Component.hpp"
#include "../UpdateThread/Array/Array.hpp"
#include "../Components/ComponentData.hpp"


class Fragment {
    private:
        BasicComponent* componentList;
        uint16_t componentAmount = 0;
        sf::Vector2<uint8_t> position;
    public:
        Fragment(sf::Vector2<uint8_t> position);
        ~Fragment();
        uint16_t getComponentAmount();
        void addComponent(Component component, sf::Vector2u position, ComponentData componentData, Array& array, bool setup);
        bool removeComponent(sf::Vector2u position, Array& array);
        BasicComponent* getComponent(sf::Vector2<uint8_t> position);
        BasicComponent* getComponent(uint16_t id);
        void calculateInputs();
        void fullTick();
        void shiftState(Array& array);
        void drawFunc(sf::RenderWindow& window, sf::Vector2u chunkPosition, void (BasicComponent::*func)(sf::RenderWindow&, sf::Vector2u));
        void drawBody(sf::RenderWindow& window, sf::Vector2u chunkPosition);
        void drawWires(sf::RenderWindow& window, sf::Vector2u chunkPosition);
        void drawPegs(sf::RenderWindow& window, sf::Vector2u chunkPosition);
};


#endif //GAME_FRAGMENT_HPP
