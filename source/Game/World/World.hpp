#ifndef GAME_WORLD_HPP
#define GAME_WORLD_HPP


#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Chunk/Chunk.hpp"
#include "Fragment/Fragment.hpp"
#include "Components/BasicComponent.hpp"


class World
{
    private:
        static const int WORLD_SIZE = 16 * 16;
        Chunk* chunks[WORLD_SIZE]{};

        static sf::Vector2i getChunk(sf::Vector2i position);

        static uint32_t getAbsolute(sf::Vector2i chunk);

        static sf::Vector2i getRelative(uint32_t absolute);

    public:
        World();

        static sf::Vector2u handlePosition(sf::Vector2i position);

        void addComponent(Component component, sf::Vector2i position, uint8_t rotation);

        void draw(sf::RenderWindow* window, sf::Vector2f playerPosition, uint8_t scale);
};


#endif //GAME_WORLD_HPP
