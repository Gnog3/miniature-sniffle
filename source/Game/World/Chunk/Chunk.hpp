#ifndef GAME_CHUNK_HPP
#define GAME_CHUNK_HPP

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <algorithm>
#include "../Fragment/Fragment.hpp"
#include "../Components/Component.hpp"
#include <iostream>


class Chunk
{
    private:
        static const int CHUNK_SIZE = 256 * 256;
        Fragment* fragments[CHUNK_SIZE];
        sf::Vector2<int8_t> position;

        static uint32_t getAbsolute(sf::Vector2u fragment);

        static sf::Vector2i getRelative(uint32_t absolute);

        static sf::Vector2i getFragment(sf::Vector2i position);

    public:
        Chunk(sf::Vector2<int8_t> position);

        void addComponent(Component component, sf::Vector2u position, uint8_t rotation);

        void draw(sf::RenderWindow* window, sf::Vector2f playerPosition, uint8_t scale);
};


#endif //GAME_CHUNK_HPP
