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

BasicComponent* World::getComponent(sf::Vector2i componentPosition)
{
    uint32_t absolute = getAbsolute(getChunk(componentPosition));
    if (chunks[absolute] == nullptr)
    {
        return nullptr;
    }
    return chunks[absolute]->getComponent(handlePosition(componentPosition));
}

void World::connect(sf::Vector2i from, sf::Vector2i to, bool in)
{
    BasicComponent* first = getComponent(from);
    BasicComponent* second = getComponent(to);

    first->connect(second, in);
}

void World::doTick()
{

}

void World::draw(sf::RenderWindow* window, sf::Vector2f playerPosition, uint8_t scale)
{
    sf::Vector2f resolution = (sf::Vector2f) window->getSize();
    sf::Vector2f topleft = playerPosition;
    sf::Vector2f bottomright = playerPosition + resolution / (float) scale;
    sf::Vector2i fromChunk = getChunk(sf::Vector2i(floor(topleft.x / 11), floor(topleft.y / 11)));
    sf::Vector2i toChunk = getChunk(sf::Vector2i(floor(bottomright.x / 11), floor(bottomright.y / 11)));

    for (int y = fromChunk.y; y <= toChunk.y; y++)
    {
        for (int x = fromChunk.x; x <= toChunk.x; x++)
        {
            uint32_t absolute = getAbsolute(sf::Vector2i(x, y));
            if (chunks[absolute] != nullptr)
            {
                sf::Vector2i position(x, y);
//                sf::RectangleShape rectangleShape(sf::Vector2f((4096 * 11) * scale, (4096 * 11) * scale));
//                rectangleShape.setOutlineColor(sf::Color::Red);
//                rectangleShape.setFillColor(sf::Color::Transparent);
//                rectangleShape.setOutlineThickness(-3);
//                rectangleShape.setPosition(((sf::Vector2f) position * (float) (4096 * 11) - playerPosition) * (float) scale);
                sf::Vector2f screenFirst = playerPosition;
                sf::Vector2f screenSecond = screenFirst + resolution / (float) scale;
                sf::Vector2f chunkFirst = (sf::Vector2f) position * (float) (11 * 4096);
                sf::Vector2f chunkSecond = sf::Vector2f(chunkFirst.x + (float) (11 * 4096 - 1),
                                                        chunkFirst.y + (float) (11 * 4096 - 1));
                sf::Vector2f intersactionFirst = sf::Vector2f(std::max(screenFirst.x, chunkFirst.x),
                                                              std::max(screenFirst.y, chunkFirst.y));
                sf::Vector2f intersactionSecond = sf::Vector2f(std::min(screenSecond.x, chunkSecond.x),
                                                               std::min(screenSecond.y, chunkSecond.y));
                intersactionFirst -= chunkFirst;
                intersactionSecond -= chunkFirst;

                sf::Vector2i firstFragment = Chunk::getFragment((sf::Vector2i) intersactionFirst / 11);
                sf::Vector2i lastFragment = Chunk::getFragment((sf::Vector2i) intersactionSecond / 11);
                chunks[absolute]->drawBody(window, playerPosition, scale, firstFragment, lastFragment);
            }
        }
    }
    for (int y = fromChunk.y; y <= toChunk.y; y++)
    {
        for (int x = fromChunk.x; x <= toChunk.x; x++)
        {
            uint32_t absolute = getAbsolute(sf::Vector2i(x, y));
            if (chunks[absolute] != nullptr)
            {
                sf::Vector2i position(x, y);
                sf::Vector2f screenFirst = playerPosition;
                sf::Vector2f screenSecond = screenFirst + resolution / (float) scale;
                sf::Vector2f chunkFirst = (sf::Vector2f) position * (float) (11 * 4096);
                sf::Vector2f chunkSecond = sf::Vector2f(chunkFirst.x + (float) (11 * 4096 - 1),
                                                        chunkFirst.y + (float) (11 * 4096 - 1));
                sf::Vector2f intersactionFirst = sf::Vector2f(std::max(screenFirst.x, chunkFirst.x),
                                                              std::max(screenFirst.y, chunkFirst.y));
                sf::Vector2f intersactionSecond = sf::Vector2f(std::min(screenSecond.x, chunkSecond.x),
                                                               std::min(screenSecond.y, chunkSecond.y));
                intersactionFirst -= chunkFirst;
                intersactionSecond -= chunkFirst;

                sf::Vector2i firstFragment = Chunk::getFragment((sf::Vector2i) intersactionFirst / 11);
                sf::Vector2i lastFragment = Chunk::getFragment((sf::Vector2i) intersactionSecond / 11);
                chunks[absolute]->drawWires(window, playerPosition, scale, firstFragment, lastFragment);
            }
        }
    }
    for (int y = fromChunk.y; y <= toChunk.y; y++)
    {
        for (int x = fromChunk.x; x <= toChunk.x; x++)
        {
            uint32_t absolute = getAbsolute(sf::Vector2i(x, y));
            if (chunks[absolute] != nullptr)
            {
                sf::Vector2i position(x, y);
                sf::Vector2f screenFirst = playerPosition;
                sf::Vector2f screenSecond = screenFirst + resolution / (float) scale;
                sf::Vector2f chunkFirst = (sf::Vector2f) position * (float) (11 * 4096);
                sf::Vector2f chunkSecond = sf::Vector2f(chunkFirst.x + (float) (11 * 4096 - 1),
                                                        chunkFirst.y + (float) (11 * 4096 - 1));
                sf::Vector2f intersactionFirst = sf::Vector2f(std::max(screenFirst.x, chunkFirst.x),
                                                              std::max(screenFirst.y, chunkFirst.y));
                sf::Vector2f intersactionSecond = sf::Vector2f(std::min(screenSecond.x, chunkSecond.x),
                                                               std::min(screenSecond.y, chunkSecond.y));
                intersactionFirst -= chunkFirst;
                intersactionSecond -= chunkFirst;

                sf::Vector2i firstFragment = Chunk::getFragment((sf::Vector2i) intersactionFirst / 11);
                sf::Vector2i lastFragment = Chunk::getFragment((sf::Vector2i) intersactionSecond / 11);
                chunks[absolute]->drawPegs(window, playerPosition, scale, firstFragment, lastFragment);
            }
        }
    }
}
