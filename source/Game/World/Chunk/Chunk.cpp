#include "Chunk.hpp"
#include "../UpdateThread/Array/Array.hpp"

uint32_t Chunk::getAbsolute(sf::Vector2u fragment)
{
    return fragment.y * 256 + fragment.x;
}

sf::Vector2i Chunk::getRelative(uint32_t absolute)
{
    return sf::Vector2i(absolute % 256, absolute / 256);
}

sf::Vector2i Chunk::getFragment(sf::Vector2i position)
{
    return position / 16;
}

Chunk::Chunk(sf::Vector2<int8_t> position)
{
    this->position = position;
    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        sf::Vector2i fragment = getRelative(i);
        //fragments[i] = new Fragment(sf::Vector2<uint8_t>(fragment));
        fragments[i] = nullptr;
    }
}

void Chunk::addComponent(Component component, sf::Vector2u position, Rotation rotation, Array& array, bool setup)
{
    sf::Vector2u fragment = position / 16u;
    uint32_t absolute = getAbsolute(fragment);
    if (fragments[absolute] == nullptr)
    {
        fragments[absolute] = new Fragment(sf::Vector2<uint8_t>(fragment));
        active++;
    }
    
    position.x %= 16;
    position.y %= 16;
    fragments[absolute]->addComponent(component, position, rotation, array, setup);
    
}

bool Chunk::removeComponent(sf::Vector2u position, Array& array)
{
    sf::Vector2u fragment = position / 16u;
    uint32_t absolute = getAbsolute(fragment);
    position.x %= 16;
    position.y %= 16;
    bool isEmpty = fragments[absolute]->removeComponent(position, array);
    if (isEmpty)
    {
        active--;
        delete fragments[absolute];
        fragments[absolute] = nullptr;
        return active == 0;
    }
    return false;
}

Fragment* Chunk::getFragment(sf::Vector2u fragment)
{
    return fragments[getAbsolute((sf::Vector2u) getFragment((sf::Vector2i) fragment))];
}

BasicComponent* Chunk::getComponent(sf::Vector2u componentPosition)
{
    uint32_t absolute = getAbsolute(componentPosition / 16u);
    if (fragments[absolute] == nullptr)
    {
        return nullptr;
    }
    componentPosition.x %= 16;
    componentPosition.y %= 16;
    return fragments[absolute]->getComponent((sf::Vector2<uint8_t>) componentPosition);
}

void Chunk::calculateInputs()
{
    for (auto& fragment : fragments)
    {
        if (fragment != nullptr)
            fragment->calculateInputs();
    }
}

void Chunk::fullTick()
{
    for (auto& fragment : fragments)
    {
        if (fragment != nullptr)
            fragment->fullTick();
    }
}
void Chunk::shiftState(Array& array)
{
    for (auto& fragment : fragments)
    {
        if (fragment != nullptr)
            fragment->shiftState(array);
    }
}
void Chunk::drawBody(sf::RenderWindow* window, sf::Vector2f playerPosition, uint8_t scale, sf::Vector2i firstFragment, sf::Vector2i lastFragment)
{
    for (int y = firstFragment.y; y <= lastFragment.y; ++y)
    {
        for (int x = firstFragment.x; x <= lastFragment.x; ++x)
        {
            uint16_t absolute = getAbsolute(sf::Vector2u(x, y));
            if (fragments[absolute] != nullptr)
            {
                sf::Vector2f chunkPosition = (sf::Vector2f) position * (float) (4096 * 11 * scale);
                fragments[absolute]->drawBody(window, playerPosition, chunkPosition, scale);
            }
        }
    }
    
    
    
    //window->draw(rectangleShape);
}

void Chunk::drawWires(sf::RenderWindow* window, sf::Vector2f playerPosition, uint8_t scale, sf::Vector2i firstFragment, sf::Vector2i lastFragment)
{
    for (int y = firstFragment.y; y <= lastFragment.y; ++y)
    {
        for (int x = firstFragment.x; x <= lastFragment.x; ++x)
        {
            uint16_t absolute = getAbsolute(sf::Vector2u(x, y));
            if (fragments[absolute] != nullptr)
            {
                sf::Vector2f chunkPosition = (sf::Vector2f) position * (float) (4096 * 11 * scale);
                fragments[absolute]->drawWires(window, playerPosition, chunkPosition, scale);
            }
        }
    }
}

void Chunk::drawPegs(sf::RenderWindow* window, sf::Vector2f playerPosition, uint8_t scale, sf::Vector2i firstFragment, sf::Vector2i lastFragment)
{
    for (int y = firstFragment.y; y <= lastFragment.y; ++y)
    {
        for (int x = firstFragment.x; x <= lastFragment.x; ++x)
        {
            uint16_t absolute = getAbsolute(sf::Vector2u(x, y));
            if (fragments[absolute] != nullptr)
            {
                sf::Vector2f chunkPosition = (sf::Vector2f) position * (float) (4096 * 11 * scale);
                fragments[absolute]->drawPegs(window, playerPosition, chunkPosition, scale);
            }
        }
    }
}
