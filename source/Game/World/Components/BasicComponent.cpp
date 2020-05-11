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
    uint32_t amount = wiredInAmount + wiredOutAmount + actualInAmount + actualOutAmount;
    BasicComponent** newPointers = new BasicComponent* [amount];
    bool isInserted = false;
    for (uint32_t i = 0; i < amount; i++)
    {
        if (i == offset)
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

void BasicComponent::removePointer(uint32_t index)
{
    uint32_t amount = wiredInAmount + wiredOutAmount + actualInAmount + actualOutAmount;
    if (amount > 0)
    {
        BasicComponent** newPointers = new BasicComponent* [amount];
        bool isInserted = false;
        for (uint32_t i = 0; i < amount + 1; i++)
        {
            if (i == index)
            {
                isInserted = true;
                continue;
            }
            newPointers[i - (isInserted ? 1 : 0)] = pointers[i];
        }
        delete[] pointers;
        pointers = newPointers;
    } else
    {
        pointers = nullptr;
    }
}

void BasicComponent::addInputWire(BasicComponent* basicComponent)
{
    for (uint8_t i = 0; i < wiredInAmount; i++)
        if (getWiredIn(i) == basicComponent)
            return;
    wiredInAmount++;
    insertPointer(basicComponent, wiredInAmount - 1);
}

void BasicComponent::addOutputWire(BasicComponent* basicComponent)
{
    for (uint8_t i = 0; i < wiredOutAmount; i++)
        if (getWiredOut(i) == basicComponent)
            return;
    wiredOutAmount++;
    insertPointer(basicComponent, wiredInAmount + wiredOutAmount - 1);
}

void BasicComponent::addInputActual(BasicComponent* basicComponent)
{
    for (uint16_t i = 0; i < actualInAmount; i++)
        if (getActualIn(i) == basicComponent)
        {
            return;
        }
    actualInAmount++;
    insertPointer(basicComponent, wiredInAmount + wiredOutAmount + actualInAmount - 1);
}

void BasicComponent::addOutputActual(BasicComponent* basicComponent)
{
    for (uint16_t i = 0; i < actualOutAmount; i++)
        if (getActualOut(i) == basicComponent)
        {
            return;
        }
    actualOutAmount++;
    insertPointer(basicComponent, wiredInAmount + wiredOutAmount + actualInAmount + actualOutAmount - 1);
}

void BasicComponent::removeInputWire(BasicComponent* basicComponent)
{
    for (uint8_t i = 0; i < wiredInAmount; i++)
    {
        if (getWiredIn(i) == basicComponent)
        {
            wiredInAmount--;
            removePointer(i);
            return;
        }
    }
    std::cout << "Pointer isn't found. wire in.";
}

void BasicComponent::removeOutputWire(BasicComponent* basicComponent)
{
    for (uint8_t i = 0; i < wiredOutAmount; i++)
    {
        if (getWiredOut(i) == basicComponent)
        {
            wiredOutAmount--;
            removePointer(wiredInAmount + i);
            return;
        }
    }
    std::cout << "Pointer isn't found. wire out.";
}

void BasicComponent::removeInputActual(BasicComponent* basicComponent)
{
    for (uint16_t i = 0; i < actualInAmount; i++)
    {
        if (getActualIn(i) == basicComponent)
        {
            actualInAmount--;
            removePointer(wiredInAmount + wiredOutAmount + i);
            return;
        }
    }
    std::cout << "Pointer isn't found. actual in.";
}

void BasicComponent::removeOutputActual(BasicComponent* basicComponent)
{
    for (uint16_t i = 0; i < actualOutAmount; i++)
    {
        if (getActualOut(i) == basicComponent)
        {
            actualOutAmount--;
            removePointer(wiredInAmount + wiredOutAmount + actualInAmount + i);
            return;
        }
    }
    std::cout << "Pointer isn't found. actual out.";
}

bool BasicComponent::insertIfNotIn(std::vector<Connection>& connections, Connection connection)
{
    for (auto& i : connections)
        if (i.component == connection.component &&
            i.isOutput == connection.isOutput)
            return false;
    connections.push_back(connection);
    return true;
}

void BasicComponent::clearActualIn()
{
    uint32_t amount = wiredInAmount + wiredOutAmount + actualOutAmount;
    BasicComponent** newPointers = new BasicComponent* [amount];
    for (uint16_t i = 0; i < wiredInAmount + wiredOutAmount; i++)
    {
        newPointers[i] = pointers[i];
    }
    for (uint16_t i = 0; i < actualOutAmount; i++)
    {
        newPointers[i] = getActualOut(i);
    }
    delete[] pointers;
    pointers = newPointers;
    actualInAmount = 0;
}

void BasicComponent::clearActualOut()
{
    uint32_t amount = wiredInAmount + wiredOutAmount + actualInAmount;
    BasicComponent** newPointers = new BasicComponent* [amount];
    for (uint32_t i = 0; i < wiredInAmount + wiredOutAmount + actualInAmount; i++)
    {
        newPointers[i] = pointers[i];
    }
    delete[] pointers;
    pointers = newPointers;
    actualOutAmount = 0;
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
    uint32_t amount = wiredInAmount + wiredOutAmount + actualInAmount + actualOutAmount;
    BasicComponent** newPointers = new BasicComponent* [amount];
    std::memcpy(newPointers, pointers, sizeof(nullptr) * amount);
    pointers = newPointers;
    //delete[] pointers;
    //no delete because.
}

void BasicComponent::scanComponents(std::vector<Connection>& connections, Scan scan, bool first)
{
    if (!insertIfNotIn(connections, Connection{this, scan}))
        return;
    
    uint32_t amount;
    BasicComponent* (BasicComponent::*func)(uint8_t);
    switch (scan)
    {
        case Input:
            amount = wiredInAmount;
            func = &BasicComponent::getWiredIn;
            break;
        case Output:
            amount = wiredOutAmount;
            func = &BasicComponent::getWiredOut;
            break;
    }
    for (uint32_t i = 0; i < amount; i++)
    {
        BasicComponent* basicComponent = (this->*func)(i);
        bool isOut = basicComponent->isWiredOutput(this);
        if (isOut && !first)
            insertIfNotIn(connections, Connection{basicComponent, true});
        else
            basicComponent->scanComponents(connections, Input, false);
    }
}

sf::Vector2<uint8_t> BasicComponent::getFragmentPosition()
{
    return fragmentPosition;
}

void BasicComponent::replacePointer(BasicComponent* from, BasicComponent* to)
{
    uint32_t amount = wiredInAmount + wiredOutAmount + actualInAmount + actualOutAmount;
    for (uint32_t i = 0; i < amount; i++)
        if (pointers[i] == from)
            pointers[i] = to;
}

void BasicComponent::fixMove(BasicComponent& old)
{
    if (old.pointers == nullptr)
        return;
    clonePointersArray();
    {
        std::vector<Connection> connections;
        scanComponents(connections, Input, false);
        for (auto& connection : connections)
            connection.component->replacePointer(&old, this);
    }
    {
        std::vector<Connection> connections;
        scanComponents(connections, Output, false);
        for (auto& connection : connections)
            connection.component->replacePointer(&old, this);
    }
}

BasicComponent::~BasicComponent()
{
    delete[] pointers;
}

void BasicComponent::recalculateActuals()
{

}

void BasicComponent::connect(BasicComponent* bc, bool in)
{
    if (in)
    {
        addInputWire(bc);
        bc->addInputWire(this);
        std::vector<Connection> connections;
        scanComponents(connections, Input, false);
        std::vector<BasicComponent*> ins;
        std::vector<BasicComponent*> outs;
        for (auto& connection : connections)
            if (connection.isOutput)
                outs.push_back(connection.component);
            else
                ins.push_back(connection.component);
        for (auto& input : ins)
            for (auto& output : outs)
            {
                input->addInputActual(output);
                if (!input->isPeg())
                    output->addOutputActual(input);
            }
    } else
    {
        addOutputWire(bc);
        bc->addInputWire(this);
        std::vector<Connection> connections;
        scanComponents(connections, Output, true);
        for (uint32_t i = 1; i < connections.size(); i++)
        {
            Connection& c = connections[i];
            if (c.component->isPeg())
                c.component->addInputActual(this);
            else
            {
                if (!c.isOutput)
                {
                    addOutputActual(c.component);
                    c.component->addInputActual(this);
                }
            }
        }
    }
}

void BasicComponent::disconnect(BasicComponent* bc, bool in)
{
    if (in)
    {
        removeInputWire(bc);
        bc->removeInputWire(this);
        std::vector<Connection> connections1;
        std::vector<Connection> connections2;
        scanComponents(connections1, Input, false);
        bc->scanComponents(connections2, Input, false);
        std::vector<BasicComponent*> ins1;
        std::vector<BasicComponent*> ins2;
        std::vector<BasicComponent*> outs1;
        std::vector<BasicComponent*> outs2;
        for (auto& connection : connections1)
            if (connection.isOutput)
                outs1.push_back(connection.component);
            else
                ins1.push_back(connection.component);
        for (auto& connection : connections2)
            if (connection.isOutput)
                outs2.push_back(connection.component);
            else
                ins2.push_back(connection.component);
        bool theSame = false;
        
        for (auto& i1: ins1)
            if (!theSame)
                for (auto& i2 : ins2)
                    if (i1 == i2)
                    {
                        theSame = true;
                        break;
                    }
        if (!theSame)
        {
            for (auto& input : ins1)
                for (auto& output : outs2)
                {
                    input->removeInputActual(output);
                    if (!input->isPeg())
                        output->removeOutputActual(input);
                }
            for (auto& input : ins2)
                for (auto& output : outs1)
                {
                    input->removeInputActual(output);
                    if (!input->isPeg())
                        output->removeOutputActual(input);
                }
        }
    } else
    {
        removeOutputWire(bc);
        bc->removeInputWire(this);
        std::vector<Connection> connections;
        bc->scanComponents(connections, Input, true);
        for (auto& c : connections)
        {
            if (c.component->isPeg())
                c.component->removeInputActual(this);
            else
            {
                if (!c.isOutput)
                {
                    removeOutputActual(c.component);
                    c.component->removeInputActual(this);
                }
            }
        }
    }
}

sf::Vector2<uint8_t> BasicComponent::getPosition() const
{
    return sf::Vector2<uint8_t>((uint8_t) 0b1111 & position, (uint8_t) ((uint8_t) 0b11110000 & position) >> (uint8_t) 4);
}

bool BasicComponent::getOutputState()
{
    return data & 0b1000u;
}

bool BasicComponent::isConnected(BasicComponent* bc, bool in)
{
    if (in)
    {
        bool t1 = false, t2 = false;
        for (uint8_t i = 0; i < wiredInAmount; i++)
        {
            if (getWiredIn(i) == bc)
            {
                t1 = true;
            }
        }
        for (uint8_t i = 0; i < bc->getWiredInAmount(); i++)
        {
            if (bc->getWiredIn(i) == this)
            {
                t2 = true;
            }
        }
        return t1 && t2;
    } else
    {
        return isWiredOutput(bc);
    }
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

Rotation BasicComponent::getRotation() const
{
    return Rotation(data & 0b11u);
}

void BasicComponent::setRotation(Rotation rotation)
{
    data = (data & 0b11111100u) | rotation;
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

void BasicComponent::drawPreviewTexture(sf::RenderWindow* window, sf::Vector2f position, uint8_t scale, Rotation rotation)
{
    sf::Texture texture;
    sf::Texture texture1;
    sf::Sprite bodySprite = getBodySprite(&texture);
    sf::Sprite pegsSprite = getPegsSprite(&texture1, sf::Color::Black, sf::Color::Black);
    
    bodySprite.setScale(sf::Vector2f(scale, scale));
    pegsSprite.setScale(sf::Vector2f(scale, scale));
    sf::Vector2f origin = sf::Vector2f(5.5f, 5.5f) - bodySprite.getOrigin();
    bodySprite.setPosition(position + sf::Vector2f(5.5f, 5.5f) * (float) scale);
    pegsSprite.setPosition(position + sf::Vector2f(5.5f, 5.5f) * (float) scale);
    bodySprite.setColor(sf::Color(255, 255, 255, 100));
    pegsSprite.setColor(sf::Color(255, 255, 255, 100));
    bodySprite.setRotation((float) rotation * 90);
    pegsSprite.setRotation((float) rotation * 90);
    window->draw(bodySprite);
    window->draw(pegsSprite);
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

sf::IntRect BasicComponent::getBodyRectangle(sf::Vector2i componentPosition)
{
    return sf::IntRect();
}

sf::IntRect BasicComponent::getInputRectangle(sf::Vector2i componentPosition)
{
    return sf::IntRect();
}

sf::IntRect BasicComponent::getOutputRectangle(sf::Vector2i componentPosition)
{
    return sf::IntRect();
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
{}

#pragma clang diagnostic pop
