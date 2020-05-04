#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"


#include <iostream>
#include "BasicComponent.hpp"

/*
 * Order:
 *  Wired Inputs
 *  Wired Outputs
 *  Actual Inputs
 */

void BasicComponent::insertPointer(BasicComponent* basicComponent, uint32_t offset)
{
    uint32_t amount = wiredInAmount + wiredOutAmount + actualInAmount + actualOutAmount;
    BasicComponent** newPointers = new BasicComponent* [amount];
    bool isInserted = false;
    for (uint32_t i = 0; i < amount; i++)
    {
        if (i == offset && !isInserted)
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
    wiredInAmount++;
    insertPointer(basicComponent, wiredInAmount - 1);
}

void BasicComponent::addOutputWire(BasicComponent* basicComponent)
{
    wiredOutAmount++;
    insertPointer(basicComponent, wiredInAmount + wiredOutAmount - 1);
}

void BasicComponent::addInputActual(BasicComponent* basicComponent)
{
    actualInAmount++;
    insertPointer(basicComponent, wiredInAmount + wiredOutAmount + actualInAmount - 1);
}

void BasicComponent::addOutputActual(BasicComponent* basicComponent)
{
    actualOutAmount++;
    insertPointer(basicComponent, wiredInAmount + wiredOutAmount + actualInAmount + actualOutAmount - 1);
}

bool BasicComponent::insertIfNotIn(std::vector<BasicComponent*>& components, BasicComponent* basicComponent)
{
    bool isIn = false;
    for (uint32_t i = 0; i < components.size(); i++)
        if (components[i] == basicComponent)
            isIn = true;
    if (isIn)
        return false;
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
    uint32_t amount = wiredInAmount + wiredOutAmount + actualInAmount;
    BasicComponent** newPointers = new BasicComponent* [amount];
    std::memcpy(newPointers, pointers, sizeof(nullptr) * amount);
    pointers = newPointers; // no delete because костыль
}

void BasicComponent::getRelatedComponents(std::vector<BasicComponent*>& components, bool in, bool out, bool outNeed)
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
                if (outNeed)
                {
                    insertIfNotIn(components, pointer);
                }
            } else
            {
                pointer->getRelatedComponents(components, true, false, false);
            }
        }
    }
    if (out)
    {
        for (uint8_t i = 0; i < wiredOutAmount; i++)
        {
            BasicComponent* pointer = getWiredOut(i);
            pointer->getRelatedComponents(components, true, false, false);
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
        if (pointers[i] == from)
            pointers[i] = to;
}

void BasicComponent::fixMove(BasicComponent& old)
{
    if (old.pointers == nullptr)
        return;
    clonePointersArray();
    std::vector<BasicComponent*> connectedComponents;
    getRelatedComponents(connectedComponents, true, true, true);
    for (uint32_t i = 0; i < connectedComponents.size(); i++)
        connectedComponents[i]->replacePointer(&old, this);
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
        basicComponent->addInputWire(this);
        std::vector<BasicComponent*> connected;
        getRelatedComponents(connected, false, true, false);
        for (uint32_t i = 1; i < connected.size(); i++)
        {
            addOutputActual(connected[i]);
            connected[i]->addInputActual(this);
        };
    } else
    {
        addInputWire(basicComponent);
        basicComponent->addInputWire(this);
    }
}

sf::Vector2<uint8_t> BasicComponent::getPosition() const
{
    return sf::Vector2<uint8_t>((uint8_t) 0b1111 & position, (uint8_t) ((uint8_t) 0b11110000 & position) >> (uint8_t) 4);
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

BasicComponent* BasicComponent::getActualOut(uint16_t index)
{
    return pointers[wiredInAmount + wiredOutAmount + actualInAmount + index];
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

bool BasicComponent::isPeg()
{
    return false;
}

void BasicComponent::drawBody(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale)
{
    static sf::Texture texture;
    static sf::Sprite sprite = getBodySprite(&texture);
    uint16_t rotation = (0b11u & data) * 90;
    sf::Vector2f position = sf::Vector2f(0b1111u & this->position, (0b11110000u & this->position) >> 4u) * 11.0f;
    sprite.setRotation(rotation);
    sprite.setScale(sf::Vector2f(scale, scale));
    sf::Vector2f calcPos = fragmentPosition + (position + sf::Vector2f(5.5f, 5.5f)) * (float) scale;
    sprite.setPosition(std::floor(calcPos.x), std::floor(calcPos.y));
    window->draw(sprite);
}

void BasicComponent::drawWires(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale)
{
    for (uint8_t i = 0; i < wiredOutAmount; i++)
    {
        sf::Vector2i fragmentDifference = (sf::Vector2i) (getWiredOut(i)->getFragmentPosition() - this->fragmentPosition);

        fragmentDifference.x = fragmentDifference.x > 128 ? fragmentDifference.x - 256 : fragmentDifference.x;
        fragmentDifference.x = fragmentDifference.x <= -128 ? fragmentDifference.x + 256 : fragmentDifference.x;
        fragmentDifference.y = fragmentDifference.y > 128 ? fragmentDifference.y - 256 : fragmentDifference.y;
        fragmentDifference.y = fragmentDifference.y <= -128 ? fragmentDifference.y + 256 : fragmentDifference.y;
        sf::Vector2f inputPoint = getWiredOut(i)->getInputPoint() * (float) scale + fragmentPosition;
        sf::Vector2f outputPoint = getOutputPoint() * (float) scale + fragmentPosition;
        sfLine sfline(sf::Vector2f(inputPoint.x + (fragmentDifference.x * (float) scale * 16 * 11),
                                   inputPoint.y + (fragmentDifference.y * (float) scale * 16 * 11)), outputPoint, sf::Color::Red, scale);
        sfline.draw(*window);
    }
    for (uint8_t i = 0; i < wiredInAmount; i++)
    {
        sf::Vector2i fragmentDifference = (sf::Vector2i) (getWiredIn(i)->getFragmentPosition() - this->fragmentPosition);
        fragmentDifference.x = fragmentDifference.x > 128 ? fragmentDifference.x - 256 : fragmentDifference.x;
        fragmentDifference.x = fragmentDifference.x <= -128 ? fragmentDifference.x + 256 : fragmentDifference.x;
        fragmentDifference.y = fragmentDifference.y > 128 ? fragmentDifference.y - 256 : fragmentDifference.y;
        fragmentDifference.y = fragmentDifference.y <= -128 ? fragmentDifference.y + 256 : fragmentDifference.y;
        sf::Vector2f first = (getWiredIn(i)->isWiredOutput(this) ? getWiredIn(i)->getOutputPoint() : getWiredIn(i)->getInputPoint()) * (float) scale + fragmentPosition;
        first += (sf::Vector2f) (fragmentDifference * 16 * 11 * (int) scale);
        sf::Vector2f second = getInputPoint() * (float) scale + fragmentPosition;
        sfLine sfline(first, second, sf::Color::Red, scale);
        sfline.draw(*window);
    }
}

void BasicComponent::drawPegs(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale)
{
    static sf::Texture texture[4];
    static sf::Sprite sprite[4]{
            getPegsSprite(&texture[0], sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255)),
            getPegsSprite(&texture[1], sf::Color(0, 0, 0, 255), sf::Color::Red),
            getPegsSprite(&texture[2], sf::Color::Red, sf::Color(0, 0, 0, 255)),
            getPegsSprite(&texture[3], sf::Color::Red, sf::Color::Red)
    };
    uint16_t rotation = (0b11u & data) * 90;
    uint8_t state = (0b11000u & data) >> 3u;
    state += 2;
    sf::Vector2f position = sf::Vector2f(0b1111u & this->position, (0b11110000u & this->position) >> 4u) * 11.0f;
    sprite[state].setRotation(rotation);
    sprite[state].setScale(sf::Vector2f(scale, scale));
    sf::Vector2f calcPos = fragmentPosition + (position + sf::Vector2f(5.5f, 5.5f)) * (float) scale;
    sprite[state].setPosition(std::floor(calcPos.x), std::floor(calcPos.y));
    window->draw(sprite[state]);
}

bool BasicComponent::isWiredOutput(BasicComponent* basicComponent)
{
    for (uint8_t i = 0; i < wiredOutAmount; i++)
        if (getWiredOut(i) == basicComponent)
            return true;
    return false;
}

sf::Vector2f BasicComponent::getInputPoint()
{
    return sf::Vector2f();
}

sf::Vector2f BasicComponent::getOutputPoint()
{
    return sf::Vector2f();
}

sf::Sprite BasicComponent::getBodySprite(sf::Texture* texture)
{
    return sf::Sprite();
}

sf::Sprite BasicComponent::getPegsSprite(sf::Texture* texture, sf::Color in, sf::Color out)
{
    return sf::Sprite();
}

void BasicComponent::update()
{

}

#pragma clang diagnostic pop
