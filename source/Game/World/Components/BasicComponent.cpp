#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"

#include "BasicComponent.hpp"

/*
 * Order:
 *  Wired Inputs
 *  Wired Outputs
 *  Actual Inputs
 */

void BasicComponent::insertPointer(BasicComponent* basicComponent, uint32_t offset)
{
    uint32_t amount = wiredInAmount + wiredOutAmount + actualInAmount + 1;
    BasicComponent** newPointers = new BasicComponent* [amount];
    bool isInserted = false;
    for (uint32_t i = 0; i < amount; i++)
    {
        if (i >= offset && !isInserted)
        {
            isInserted = true;
            newPointers[i] = basicComponent;
            continue;
        }
        newPointers[i] = pointers[i - (isInserted ? 1 : 0)];
    }
    delete[] pointers;
    pointers = newPointers;
}

void BasicComponent::addInputWire(BasicComponent* basicComponent)
{
    insertPointer(basicComponent, wiredInAmount);
}

void BasicComponent::addOutputWire(BasicComponent* basicComponent)
{
    insertPointer(basicComponent, wiredInAmount + wiredOutAmount);
}

void BasicComponent::addInputActual(BasicComponent* basicComponent)
{
    insertPointer(basicComponent, wiredInAmount + wiredOutAmount + actualInAmount);
}

BasicComponent* BasicComponent::getWiredIn(uint8_t index)
{
    return pointers[index];
}

BasicComponent* BasicComponent::getWiredOut(uint8_t index)
{
    return pointers[wiredInAmount + index];
}

BasicComponent* BasicComponent::getActualIn(uint16_t index)
{
    return pointers[wiredInAmount + wiredOutAmount + index];
}

bool BasicComponent::insertIfNotIn(std::vector<BasicComponent*>& components, BasicComponent* basicComponent)
{
    bool isIn = false;
    for (uint32_t i = 0; i < components.size(); i++)
    {
        if (components[i] == basicComponent)
        {
            isIn = true;
        }
    }
    if (isIn)
    {
        return false;
    }
    components.push_back(basicComponent);
    return true;
}

BasicComponent::BasicComponent(Component component, sf::Vector2<uint8_t> position, sf::Vector2<uint8_t> fragmentPosition, uint8_t rotation)
{
    this->position += position.x;
    this->position += position.y << (uint8_t) 4;
    this->fragmentPosition = fragmentPosition;
    data = rotation;
}

void BasicComponent::clonePointersArray()
{

}

void BasicComponent::getRelatedComponents(std::vector<BasicComponent*>& components, bool in, bool out)
{
    if (!insertIfNotIn(components, this))
    {
        return;
    }
    if (in)
    {
        for (uint8_t i = 0; i < wiredInAmount; i++)
        {
            BasicComponent* pointer = getWiredIn(i);
            if (pointer->isWiredOutput(this))
            {
                insertIfNotIn(components, pointer);
            } else
            {
                pointer->getRelatedComponents(components, true, false);
            }
        }
    }
    if (out)
    {
        for (uint8_t i = 0; i < wiredOutAmount; i++)
        {
            BasicComponent* pointer = getWiredOut(i);
            pointer->getRelatedComponents(components, true, false);
        }
    }
}

sf::Vector2<uint8_t> BasicComponent::getFragmentPosition()
{
    return fragmentPosition;
}

void BasicComponent::replacePointer(BasicComponent* from, BasicComponent* to)
{
    uint32_t amount = wiredInAmount + wiredOutAmount + actualInAmount;
    for (uint32_t i = 0; i < amount; i++)
    {
        if (pointers[i] == from)
        {
            pointers[i] = to;
        }
    }
}

void BasicComponent::fixMove(BasicComponent& old)
{
    if (old.pointers == nullptr)
    {
        return;
    }
    std::vector<BasicComponent*> connectedComponents;
    getRelatedComponents(connectedComponents, true, true);
    for (uint32_t i = 0; i < connectedComponents.size(); i++)
    {
        connectedComponents[i]->replacePointer(&old, this);
    }
}

BasicComponent::~BasicComponent()
{
    delete[] pointers;
}

void BasicComponent::connect(BasicComponent* basicComponent, bool in)
{
    if (!in)
    {
        addOutputWire(basicComponent);
        wiredOutAmount++;
        basicComponent->addInputWire(this);
        basicComponent->setWiredInAmount(basicComponent->getWiredInAmount() + 1);
    }
}

sf::Vector2<uint8_t> BasicComponent::getPosition() const
{
    return sf::Vector2<uint8_t>((uint8_t) 0b1111 & position, (uint8_t) ((uint8_t) 0b11110000 & position) >> (uint8_t) 4);
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

void BasicComponent::setWiredInAmount(uint8_t value)
{
    wiredInAmount = value;
}

void BasicComponent::setWiredOutAmount(uint8_t value)
{
    wiredOutAmount = value;
}

void BasicComponent::setActualInAmount(uint16_t value)
{
    actualInAmount = value;
}

bool BasicComponent::isWiredOutput(BasicComponent* basicComponent)
{
    for (uint8_t i = 0; i < wiredOutAmount; i++)
    {
        if (getWiredOut(i) == basicComponent)
        {
            return true;
        }
    }
    return false;
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

#pragma clang diagnostic pop
