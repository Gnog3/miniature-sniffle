#ifndef GAME_CHUNK_HPP
#define GAME_CHUNK_HPP
#define CHUNK_SIZE 256 * 256

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <algorithm>
#include "../../Rotation.hpp"
#include "../Fragment/Fragment.hpp"
#include "../Components/Component.hpp"
#include "../UpdateThread/Array/Array.hpp"
#include "../Components/ComponentData.hpp"
#include <iostream>


class Chunk {
    private:
        Fragment* fragments[CHUNK_SIZE];
        uint32_t active = 0;
        sf::Vector2<uint8_t> position;
    public:
        static uint32_t getAbsolute(sf::Vector2u fragment);
        static sf::Vector2u getRelative(uint32_t absolute);
        static sf::Vector2u getFragmentPosition(sf::Vector2u position);
        Chunk(sf::Vector2<uint8_t> position);
        void addComponent(Component component, sf::Vector2u position, ComponentData componentData, Array& array, bool setup);
        bool removeComponent(sf::Vector2u position, Array& array);
        Fragment* getFragment(sf::Vector2u position);
        BasicComponent* getComponent(sf::Vector2u componentPosition);
        void calculateInputs();
        void fullTick();
        void shiftState(Array& array);
        void drawFunc(sf::RenderWindow& window, void (Fragment::* func)(sf::RenderWindow&, sf::Vector2u));
        void drawBody(sf::RenderWindow& window);
        void drawWires(sf::RenderWindow& window);
        void drawPegs(sf::RenderWindow& window);
};


#endif //GAME_CHUNK_HPP
