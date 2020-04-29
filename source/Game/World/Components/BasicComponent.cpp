

#include "BasicComponent.hpp"

/*
 * Order:
 *  Wired Inputs
 *  Wired Outputs
 *  Actual Inputs
 *  Actual Outputs
 */

void BasicComponent::addInputWire(BasicComponent* basicComponent)
{
}

void BasicComponent::addOutputWire(BasicComponent* basicComponent)
{

}

void BasicComponent::addInputActual(BasicComponent* basicComponent)
{

}

void BasicComponent::addOutputActual(BasicComponent* basicComponent)
{

}

BasicComponent* BasicComponent::getWiredIn(uint8_t index)
{
    if (index >= wiredInAmount)
    {
        return nullptr;
    }
    return pointers[index];
}

BasicComponent* BasicComponent::getWiredOut(uint8_t index)
{
    if (index >= wiredOutAmount)
    {
        return nullptr;
    }
    return pointers[wiredInAmount + index];
}

BasicComponent* BasicComponent::getActualIn(uint16_t index)
{
    if (index >= actualInAmount)
    {
        return nullptr;
    }
    return pointers[wiredInAmount + wiredOutAmount + index];
}

BasicComponent* BasicComponent::getActualOut(uint16_t index)
{
    if (index >= actualOutAmount)
    {
        return nullptr;
    }
    return pointers[wiredInAmount + wiredOutAmount + actualInAmount + index];
}

BasicComponent::BasicComponent(Component component, sf::Vector2u position, uint8_t rotation)
{
    this->position += position.x;
    this->position += position.y << 4;
    data = rotation;
}

BasicComponent &BasicComponent::operator=(BasicComponent &other)
{
    if (pointers != nullptr)
    {
        throw "Kick Gnog 1";
    }
    if (this == &other)
    {
        throw "Kick Gnog 2";
    }
    position = other.position;
    data = other.data;
    wiredInAmount = other.wiredInAmount;
    wiredOutAmount = other.wiredOutAmount;
    actualInAmount = other.actualInAmount;
    actualOutAmount = other.actualOutAmount;
    if (other.pointers == nullptr)
    {
        return *this;
    }
    uint32_t amount = wiredInAmount + wiredOutAmount + actualInAmount + actualOutAmount;
    pointers = new BasicComponent* [amount];
    for (uint32_t i = 0; i < amount; i++)
    {
        pointers[i] = other.pointers[i];
    }
    for (uint16_t i = 0; i < actualOutAmount; i++)
    {
        BasicComponent* pointer = getActualOut(i);
        for (uint16_t j = 0; j < pointer->getActualInAmount(); j++)
        {

        }
    }
}

BasicComponent::~BasicComponent()
{
    delete[] pointers;
}

BasicComponent* BasicComponent::connect(BasicComponent* basicComponent)
{

}

uint8_t BasicComponent::getPosition() const
{
    return position;
}

uint8_t BasicComponent::getWiredInAmount() const
{
    return wiredInAmount;
}

uint8_t BasicComponent::getWiredOutAmount() const
{
    return wiredOutAmount;
}

uint16_t BasicComponent::getActualInAmount() const
{
    return actualInAmount;
}

uint16_t BasicComponent::getActualOutAmount() const
{
    return actualOutAmount;
}

sf::Sprite BasicComponent::getSprite(sf::Texture* texture, sf::Color in, sf::Color out)
{
    return sf::Sprite();
}

void BasicComponent::update()
{

}

void BasicComponent::draw(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale)
{

}
