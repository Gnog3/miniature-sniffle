#ifndef GAME_CHUNK_HPP
#define GAME_CHUNK_HPP

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <algorithm>
#include "../../Rotation.hpp"
#include "../Fragment/Fragment.hpp"
#include "../Components/Component.hpp"
#include <iostream>


class Chunk
{
    private:
        static const int CHUNK_SIZE = 256 * 256;
        Fragment* fragments[CHUNK_SIZE];
        sf::Vector2<int8_t> position;
    public:
        static uint32_t getAbsolute(sf::Vector2u fragment);
        static sf::Vector2i getRelative(uint32_t absolute);
        static sf::Vector2i getFragment(sf::Vector2i position);
        Chunk(sf::Vector2<int8_t> position);
        void addComponent(Component component, sf::Vector2u position, Rotation rotation);
        Fragment* getFragment(sf::Vector2u fragment);
        BasicComponent* getComponent(sf::Vector2u componentPosition);
        void drawBody(sf::RenderWindow* window, sf::Vector2f playerPosition, uint8_t scale, sf::Vector2i firstFragment, sf::Vector2i lastFragment);
        void drawWires(sf::RenderWindow* window, sf::Vector2f playerPosition, uint8_t scale, sf::Vector2i firstFragment, sf::Vector2i lastFragment);
        void drawPegs(sf::RenderWindow* window, sf::Vector2f playerPosition, uint8_t scale, sf::Vector2i firstFragment, sf::Vector2i lastFragment);
};


#endif //GAME_CHUNK_HPP
