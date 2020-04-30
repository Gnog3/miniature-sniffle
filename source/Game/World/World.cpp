#include <iostream>
#include "World.hpp"

sf::Vector2i World::getChunk(sf::Vector2i position)
{
    position.x = position.x < 0 ? (position.x - 4095) / 4096 : position.x / 4096;
    position.y = position.y < 0 ? (position.y - 4095) / 4096 : position.y / 4096;
    return position;
}

uint32_t World::getAbsolute(sf::Vector2i chunk)
{
    return (chunk.y + 8) * 16 + (chunk.x + 8);
}

sf::Vector2i World::getRelative(uint32_t absolute)
{
    uint32_t y = absolute / 16;
    uint32_t x = absolute % 16;
    return sf::Vector2i(x - 8, y - 8);
}

World::World()
{
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        //chunks[i] = new Chunk((sf::Vector2<int8_t>)getRelative(i));
        chunks[i] = nullptr;
    }
}

sf::Vector2u World::handlePosition(sf::Vector2i position)
{
    position.x = position.x < 0 ? (4096 + (position.x % 4096)) % 4096 : position.x % 4096;
    position.y = position.y < 0 ? (4096 + (position.y % 4096)) % 4096 : position.y % 4096;
    return (sf::Vector2u) position;
}

void World::addComponent(Component component, sf::Vector2i position, uint8_t rotation)
{
    sf::Vector2i chunk = getChunk(position);

    uint32_t absolute = getAbsolute(chunk);

    if (chunks[absolute] == nullptr)
    {
        chunks[absolute] = new Chunk((sf::Vector2<int8_t>) chunk);
    }

    chunks[absolute]->addComponent(component, handlePosition(position), rotation);
}

void World::connect(sf::Vector2i from, sf::Vector2i to)
{
    BasicComponent* first = chunks[getAbsolute(getChunk(from))]->getComponent(handlePosition(from));
    BasicComponent* second = chunks[getAbsolute(getChunk(to))]->getComponent(handlePosition(to));
    first->connect(second);
}

void World::draw(sf::RenderWindow* window, sf::Vector2f playerPosition, uint8_t scale)
{
    sf::Vector2f resolution = (sf::Vector2f) window->getSize();
    sf::Vector2f topleft = playerPosition;
    sf::Vector2f bottomright = playerPosition + resolution / (float) scale;
    sf::Vector2i fromChunk = getChunk(sf::Vector2i(floor(topleft.x / 5), floor(topleft.y / 5)));
    sf::Vector2i toChunk = getChunk(sf::Vector2i(floor(bottomright.x / 5), floor(bottomright.y / 5)));

    for (int y = fromChunk.y; y <= toChunk.y; y++)
    {
        for (int x = fromChunk.x; x <= toChunk.x; x++)
        {
            uint32_t absolute = getAbsolute(sf::Vector2i(x, y));
            if (chunks[absolute] != nullptr)
            {
                chunks[absolute]->draw(window, playerPosition, scale);
            }
        }
    }
}
