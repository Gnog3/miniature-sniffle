
#include "Fragment.hpp"

Fragment::Fragment(sf::Vector2<uint8_t> position)
{
    componentList = nullptr;
    if (position.x > 100 || position.y > 100)
    {
        int a = 5;
        int b = 6;
    }
    this->position = position;
}

Fragment::~Fragment()
{

}

uint16_t Fragment::getComponentAmount()
{
    return componentAmount;
}

void Fragment::addComponent(Component component, sf::Vector2u position, Rotation rotation)
{
    componentAmount++;
    BasicComponent* newComponentList = new BasicComponent[componentAmount];
    if (componentList != nullptr)
    {
        //TODO: жесткий костыль, переделать нафиг все
        for (int i = 0; i < componentAmount - 1; i++)
        {
            std::memcpy(newComponentList + i, componentList + i, sizeof(BasicComponent));
            newComponentList[i].fixMove(componentList[i]);
        }
        delete[] componentList;
    }
    componentList = newComponentList;


    switch (component)
    {
        case Component::Inverter:
            new(&componentList[componentAmount - 1]) class Inverter((sf::Vector2<uint8_t>) position, this->position, rotation);
            break;
        case Component::Blotter:
            new(&componentList[componentAmount - 1]) class Blotter((sf::Vector2<uint8_t>) position, this->position, rotation);
            break;
        case Component::Peg:
            new(&componentList[componentAmount - 1]) class Peg((sf::Vector2<uint8_t>) position, this->position);
            break;
    }
}

BasicComponent* Fragment::getComponent(sf::Vector2<uint8_t> position)
{
    for (uint16_t i = 0; i < componentAmount; i++)
    {
        sf::Vector2<uint8_t> componentPosition = componentList[i].getPosition();
        if (componentPosition == position)
            return &componentList[i];
    }
    return nullptr;
}

BasicComponent* Fragment::getComponent(uint16_t id)
{
    return &componentList[id];
}

void Fragment::drawBody(sf::RenderWindow* window, sf::Vector2f playerPosition, sf::Vector2f chunkPosition, uint8_t scale)
{
    sf::RectangleShape rectangleShape(sf::Vector2f((16 * 11) * scale - 2, (16 * 11) * scale - 2));
    rectangleShape.setOutlineColor(sf::Color::Blue);
    rectangleShape.setFillColor(sf::Color::Transparent);
    rectangleShape.setOutlineThickness(-3);
    rectangleShape.setPosition(
            ((sf::Vector2f) position * (float) (16 * 11) - playerPosition) * (float) scale + sf::Vector2f(2, 2) +
            chunkPosition);

    sf::Vector2f fragmentPosition = ((sf::Vector2f) position * (float) (16 * 11) - playerPosition) * (float) scale + chunkPosition;

    for (int i = 0; i < componentAmount; i++)
    {
        componentList[i].drawBody(window, fragmentPosition, scale);
    }

    window->draw(rectangleShape);
}

void Fragment::drawWires(sf::RenderWindow* window, sf::Vector2f playerPosition, sf::Vector2f chunkPosition, uint8_t scale)
{
    sf::Vector2f fragmentPosition = ((sf::Vector2f) position * (float) (16 * 11) - playerPosition) * (float) scale + chunkPosition;
    for (int i = 0; i < componentAmount; i++)
    {
        componentList[i].drawWires(window, fragmentPosition, scale);
    }
}

void Fragment::drawPegs(sf::RenderWindow* window, sf::Vector2f playerPosition, sf::Vector2f chunkPosition, uint8_t scale)
{
    sf::Vector2f fragmentPosition = ((sf::Vector2f) position * (float) (16 * 11) - playerPosition) * (float) scale + chunkPosition;
    for (int i = 0; i < componentAmount; i++)
    {
        componentList[i].drawPegs(window, fragmentPosition, scale);
    }
}
