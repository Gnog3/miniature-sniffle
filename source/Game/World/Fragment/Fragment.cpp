
#include "Fragment.hpp"

Fragment::Fragment(sf::Vector2<uint8_t> position)
{
    componentList = nullptr;
    this->position = position;
}

Fragment::~Fragment()
{

}

void Fragment::addComponent(Component component, sf::Vector2u position, uint8_t rotation)
{
    componentAmount++;
    BasicComponent* newComponentList = new BasicComponent[componentAmount];
    if (componentList != nullptr)
    {
        //TODO: жесткий костыль, переделать нахуй все
        std::memcpy(newComponentList, componentList, sizeof(BasicComponent) * (componentAmount - 1));
        for (int i = 0; i < componentAmount - 1; i++)
        {
            newComponentList[i].fixMove(componentList[i]);
        }
        delete[] componentList;
    }
    componentList = newComponentList;


    switch (component)
    {
        case Component::Inverter:
            new(&componentList[componentAmount - 1]) class Inverter((sf::Vector2<uint8_t>) position, this->position, rotation);
            //componentList[componentAmount - 1] = Inverter(position, rotation);
            break;
        case Component::Blotter:
            new(&componentList[componentAmount - 1]) class Blotter((sf::Vector2<uint8_t>) position, this->position, rotation);
            //componentList[componentAmount - 1] = Blotter(position, rotation);
            break;
    }
}

BasicComponent* Fragment::getComponent(sf::Vector2<uint8_t> position)
{
    for (uint16_t i = 0; i < componentAmount; i++)
    {
        sf::Vector2<uint8_t> componentPosition = componentList[i].getPosition();
        if (componentPosition == position)
        {
            return &componentList[i];
        }
    }
    return nullptr;
}

void Fragment::draw(sf::RenderWindow* window, sf::Vector2f playerPosition, sf::Vector2f chunkPosition, uint8_t scale)
{
    sf::RectangleShape rectangleShape(sf::Vector2f((16 * 5) * scale - 2, (16 * 5) * scale - 2));
    rectangleShape.setOutlineColor(sf::Color::Blue);
    rectangleShape.setFillColor(sf::Color::Transparent);
    rectangleShape.setOutlineThickness(-3);
    rectangleShape.setPosition(
            ((sf::Vector2f) position * (float) (16 * 5) - playerPosition) * (float) scale + sf::Vector2f(2, 2) +
            chunkPosition);


    sf::Vector2f fragmentPosition = ((sf::Vector2f) position * (float) (16 * 5) - playerPosition) * (float) scale + chunkPosition;

    for (int i = 0; i < componentAmount; i++)
    {
        componentList[i].draw(window, fragmentPosition, scale);
    }
    window->draw(rectangleShape);
}
