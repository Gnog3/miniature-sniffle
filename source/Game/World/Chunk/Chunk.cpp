#include "Chunk.hpp"

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

void Chunk::addComponent(Component component, sf::Vector2u position, uint8_t rotation)
{
    sf::Vector2u fragment = position / (uint32_t) 16;
    uint32_t absolute = getAbsolute(fragment);
    if (fragments[absolute] == nullptr)
    {
        fragments[absolute] = new Fragment(sf::Vector2<uint8_t>(fragment));
    }

    position.x %= 16;
    position.y %= 16;
    fragments[absolute]->addComponent(component, position, rotation);

}

BasicComponent* Chunk::getComponent(sf::Vector2u componentPosition)
{
    uint32_t absolute = getAbsolute(componentPosition / (uint32_t) 16);
    componentPosition.x %= 16;
    componentPosition.y %= 16;
    return fragments[absolute]->getComponent((sf::Vector2<uint8_t>) componentPosition);
}

void Chunk::draw(sf::RenderWindow* window, sf::Vector2f playerPosition, uint8_t scale)
{
    sf::Vector2f resolution = (sf::Vector2f) window->getSize();
    sf::RectangleShape rectangleShape(sf::Vector2f((4096 * 5) * scale, (4096 * 5) * scale));
    rectangleShape.setOutlineColor(sf::Color::Red);
    rectangleShape.setFillColor(sf::Color::Transparent);
    rectangleShape.setOutlineThickness(-3);
    rectangleShape.setPosition(((sf::Vector2f) position * (float) (4096 * 5) - playerPosition) * (float) scale);
    sf::Vector2f screenFirst = playerPosition;
    sf::Vector2f screenSecond = screenFirst + resolution / (float) scale;
    sf::Vector2f chunkFirst = (sf::Vector2f) position * (float) (5 * 4096);
    sf::Vector2f chunkSecond = sf::Vector2f(chunkFirst.x + (float) (5 * 4096 - 1),
                                            chunkFirst.y + (float) (5 * 4096 - 1));
    sf::Vector2f intersactionFirst = sf::Vector2f(std::max(screenFirst.x, chunkFirst.x),
                                                  std::max(screenFirst.y, chunkFirst.y));
    sf::Vector2f intersactionSecond = sf::Vector2f(std::min(screenSecond.x, chunkSecond.x),
                                                   std::min(screenSecond.y, chunkSecond.y));
    intersactionFirst -= chunkFirst;
    intersactionSecond -= chunkFirst;

    sf::Vector2i firstFragment = getFragment((sf::Vector2i) intersactionFirst / 5);
    sf::Vector2i lastFragment = getFragment((sf::Vector2i) intersactionSecond / 5);

    for (int y = firstFragment.y; y <= lastFragment.y; ++y)
    {
        for (int x = firstFragment.x; x <= lastFragment.x; ++x)
        {
            uint16_t absolute = getAbsolute(sf::Vector2u(x, y));
            if (fragments[absolute] != nullptr)
            {
                sf::Vector2f chunkPosition = (sf::Vector2f) position * (float) (4096 * 5 * scale);
                fragments[absolute]->draw(window, playerPosition, chunkPosition, scale);
            }
        }
    }
    window->draw(rectangleShape);
}
