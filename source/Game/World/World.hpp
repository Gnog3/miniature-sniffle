#ifndef GAME_WORLD_HPP
#define GAME_WORLD_HPP


#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "../Rotation.hpp"
#include "Chunk/Chunk.hpp"
#include "Fragment/Fragment.hpp"
#include "Components/BasicComponent.hpp"


class World
{
    private:
        static const int WORLD_SIZE = 16 * 16;
        Chunk* chunks[WORLD_SIZE]{};

    public:
        static sf::Vector2i getChunk(sf::Vector2i position);
        static uint32_t getAbsolute(sf::Vector2i chunk);
        static sf::Vector2i getRelative(uint32_t absolute);
        World();
        static sf::Vector2u handlePosition(sf::Vector2i position);
        void addComponent(Component component, sf::Vector2i position, Rotation rotation);
        void removeComponent(sf::Vector2i position);
        Fragment* getFragmentFromPoint(sf::Vector2i point);
        BasicComponent* getComponent(sf::Vector2i componentPosition);
        void connect(sf::Vector2i from, sf::Vector2i to, bool in = false);
        void disconnect(sf::Vector2i from, sf::Vector2i to, bool in = false);
        bool isConnected(sf::Vector2i from, sf::Vector2i to, bool in = false);
        void fullTick();
        void draw(sf::RenderWindow* window, sf::Vector2f playerPosition, uint8_t scale);
};


#endif //GAME_WORLD_HPP
