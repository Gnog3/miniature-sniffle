#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"


#include "BasicComponent.hpp"

/*
 * Order:
 *  Wired Inputs
 *  Wired Outputs
 *  Actual Inputs
 */

void BasicComponent::insertPointer(BasicComponent* basicComponent, uint32_t offset) {
    uint32_t amount = wiredInAmount + wiredOutAmount + actualInAmount + actualOutAmount;
    BasicComponent** newPointers = new BasicComponent* [amount];
    bool isInserted = false;
    for (uint32_t i = 0; i < amount; i++) {
        if (i == offset) {
            isInserted = true;
            newPointers[i] = basicComponent;
            continue;
        }
        newPointers[i] = pointers[i - (isInserted ? 1 : 0)];
    }
    delete[] pointers;
    pointers = newPointers;
}

void BasicComponent::removePointer(uint32_t index) {
    uint32_t amount = wiredInAmount + wiredOutAmount + actualInAmount + actualOutAmount;
    if (amount > 0) {
        BasicComponent** newPointers = new BasicComponent* [amount];
        bool isFound = false;
        for (uint32_t i = 0; i < amount + 1; i++) {
            if (i == index) {
                isFound = true;
                continue;
            }
            newPointers[i - (isFound ? 1 : 0)] = pointers[i];
        }
        delete[] pointers;
        pointers = newPointers;
    } else {
        pointers = nullptr;
    }
}

void BasicComponent::addInputWire(BasicComponent* basicComponent) {
//    for (uint8_t i = 0; i < wiredInAmount; i++)
//        if (getWiredIn(i) == basicComponent)
//            return;
    wiredInAmount++;
    insertPointer(basicComponent, wiredInAmount - 1);
}

void BasicComponent::addOutputWire(BasicComponent* basicComponent) {
//    for (uint8_t i = 0; i < wiredOutAmount; i++)
//        if (getWiredOut(i) == basicComponent)
//            return;
    wiredOutAmount++;
    insertPointer(basicComponent, wiredInAmount + wiredOutAmount - 1);
}

void BasicComponent::addInputActual(BasicComponent* basicComponent) {
    for (uint16_t i = 0; i < actualInAmount; i++)
        if (getActualIn(i) == basicComponent) {
            return;
        }
    actualInAmount++;
    insertPointer(basicComponent, wiredInAmount + wiredOutAmount + actualInAmount - 1);
}

void BasicComponent::addOutputActual(BasicComponent* basicComponent) {
    for (uint16_t i = 0; i < actualOutAmount; i++)
        if (getActualOut(i) == basicComponent) {
            return;
        }
    actualOutAmount++;
    insertPointer(basicComponent, wiredInAmount + wiredOutAmount + actualInAmount + actualOutAmount - 1);
}

void BasicComponent::removeInputWire(BasicComponent* basicComponent) {
    for (uint8_t i = 0; i < wiredInAmount; i++) {
        if (getWiredIn(i) == basicComponent) {
            wiredInAmount--;
            removePointer(i);
            return;
        }
    }
    std::cout << "Pointer isn't found. wire in." << std::endl;
}

void BasicComponent::removeOutputWire(BasicComponent* basicComponent) {
    for (uint8_t i = 0; i < wiredOutAmount; i++) {
        if (getWiredOut(i) == basicComponent) {
            wiredOutAmount--;
            removePointer(wiredInAmount + i);
            return;
        }
    }
    std::cout << "Pointer isn't found. wire out." << std::endl;
}

void BasicComponent::removeInputActual(BasicComponent* basicComponent) {
    for (uint16_t i = 0; i < actualInAmount; i++) {
        if (getActualIn(i) == basicComponent) {
            actualInAmount--;
            removePointer(wiredInAmount + wiredOutAmount + i);
            return;
        }
    }
    std::cout << "Pointer isn't found. actual in." << std::endl;
}

void BasicComponent::removeOutputActual(BasicComponent* basicComponent) {
    for (uint16_t i = 0; i < actualOutAmount; i++) {
        if (getActualOut(i) == basicComponent) {
            actualOutAmount--;
            removePointer(wiredInAmount + wiredOutAmount + actualInAmount + i);
            return;
        }
    }
    std::cout << "Pointer isn't found. actual out." << std::endl;
}

bool BasicComponent::insertIfNotIn(std::vector<Connection>& connections, Connection connection) {
    for (auto& i : connections)
        if (i.component == connection.component &&
            i.isOutput == connection.isOutput)
            return false;
    connections.push_back(connection);
    return true;
}

//void BasicComponent::clearActualIn()
//{
//    uint32_t amount = wiredInAmount + wiredOutAmount + actualOutAmount;
//    BasicComponent** newPointers = new BasicComponent* [amount];
//    for (uint16_t i = 0; i < wiredInAmount + wiredOutAmount; i++)
//    {
//        newPointers[i] = pointers[i];
//    }
//    for (uint16_t i = 0; i < actualOutAmount; i++)
//    {
//        newPointers[i] = getActualOut(i);
//    }
//    delete[] pointers;
//    pointers = newPointers;
//    actualInAmount = 0;
//}
//
//void BasicComponent::clearActualOut()
//{
//    uint32_t amount = wiredInAmount + wiredOutAmount + actualInAmount;
//    BasicComponent** newPointers = new BasicComponent* [amount];
//    for (uint32_t i = 0; i < wiredInAmount + wiredOutAmount + actualInAmount; i++)
//    {
//        newPointers[i] = pointers[i];
//    }
//    delete[] pointers;
//    pointers = newPointers;
//    actualOutAmount = 0;
//}

BasicComponent::BasicComponent(sf::Vector2<uint8_t> position, sf::Vector2<uint8_t> fragmentPosition, uint8_t componentData) {
    this->position += position.x;
    this->position += position.y << (uint8_t) 4;
    this->fragmentPosition = fragmentPosition;
    data = componentData;
}

void BasicComponent::clonePointersArray() {
    uint32_t amount = wiredInAmount + wiredOutAmount + actualInAmount + actualOutAmount;
    BasicComponent** newPointers = new BasicComponent* [amount];
    std::memcpy(newPointers, pointers, sizeof(nullptr) * amount);
    pointers = newPointers;
    //delete[] pointers;
    //no delete because.
}

void BasicComponent::scanComponents(std::vector<Connection>& connections) {
    if (!insertIfNotIn(connections, Connection{this, false}))
        return;
    for (uint32_t i = 0; i < wiredInAmount; i++) {
        BasicComponent* basicComponent = getWiredIn(i);
        bool isOut = basicComponent->isWiredOutput(this);
        if (isOut)
            insertIfNotIn(connections, Connection{basicComponent, true});
        else
            basicComponent->scanComponents(connections);
    }
}

sf::Vector2<uint8_t> BasicComponent::getFragmentPosition() {
    return fragmentPosition;
}

void BasicComponent::replacePointer(BasicComponent* from, BasicComponent* to) {
    uint32_t amount = wiredInAmount + wiredOutAmount + actualInAmount + actualOutAmount;
    for (uint32_t i = 0; i < amount; i++)
        if (pointers[i] == from)
            pointers[i] = to;
}

void BasicComponent::fixMove(BasicComponent* old, Array& array, bool setup) {
    if (!setup)
        array.replaceComponent(old, this);
    if (old->pointers == nullptr)
        return;
    clonePointersArray();
    replacePointer(old, this);
    std::vector<Connection> connections1;
    std::vector<Connection> connections2;
    old->scanComponents(connections1);
    for (uint8_t i = 0; i < old->getWiredOutAmount(); i++)
        old->getWiredOut(i)->scanComponents(connections2);
    for (auto& connection : connections1)
        connection.component->replacePointer(old, this);
    for (auto& connection : connections2)
        connection.component->replacePointer(old, this);
}

BasicComponent::~BasicComponent() {
    delete[] pointers;
}

void BasicComponent::connect(BasicComponent* basicComponent, bool in, Array& array, bool setup) {
    if (in) {
        addInputWire(basicComponent);
        basicComponent->addInputWire(this);
        std::vector<Connection> connections;
        scanComponents(connections);
        std::vector<BasicComponent*> ins;
        std::vector<BasicComponent*> outs;
        for (auto& connection : connections)
            if (connection.isOutput)
                outs.push_back(connection.component);
            else
                ins.push_back(connection.component);
        for (auto& input : ins)
            for (auto& output : outs) {
                
                input->addInputActual(output);
                if (input->getComponent() != Peg) {
                    if (!setup)
                        array.add(input);
                    output->addOutputActual(input);
                }
            }
    } else {
        addOutputWire(basicComponent);
        basicComponent->addInputWire(this);
        std::vector<Connection> connections;
        basicComponent->scanComponents(connections);
        for (auto& c : connections) {
            if (c.component->getComponent() == Peg)
                c.component->addInputActual(this);
            else {
                if (!c.isOutput) {
                    if (!setup)
                        array.add(c.component);
                    addOutputActual(c.component);
                    c.component->addInputActual(this);
                }
            }
        }
    }
}

void BasicComponent::disconnect(BasicComponent* bc, bool in, Array& array, bool setup) {
    if (in) {
        removeInputWire(bc);
        bc->removeInputWire(this);
        std::vector<Connection> connections1;
        std::vector<Connection> connections2;
        scanComponents(connections1);
        bc->scanComponents(connections2);
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
            if (!theSame) {
                for (auto& i2 : ins2)
                    if (i1 == i2) {
                        theSame = true;
                        break;
                    }
            } else
                break;
        if (!theSame) {
            std::vector<BasicComponent*> sharedOuts;
            for (auto& o1: outs1)
                for (auto& o2: outs2)
                    if (o1 == o2)
                        sharedOuts.push_back(o1);
            for (auto& input : ins1)
                for (auto& output : outs2)
                    if (sharedOuts.empty()) {
                        input->removeInputActual(output);
                        if (input->getComponent() != Peg) {
                            if (!setup)
                                array.add(input);
                            output->removeOutputActual(input);
                        }
                    } else
                        for (auto& shared : sharedOuts)
                            if (output != shared) {
                                input->removeInputActual(output);
                                if (input->getComponent() != Peg) {
                                    if (!setup)
                                        array.add(input);
                                    output->removeOutputActual(input);
                                }
                                break;
                            }
            for (auto& input: ins2)
                for (auto& output: outs1)
                    if (sharedOuts.empty()) {
                        input->removeInputActual(output);
                        if (input->getComponent() != Peg) {
                            if (!setup)
                                array.add(input);
                            output->removeOutputActual(input);
                        }
                    } else
                        for (auto& shared: sharedOuts)
                            if (output != shared) {
                                input->removeInputActual(output);
                                if (input->getComponent() != Peg) {
                                    if (!setup)
                                        array.add(input);
                                    output->removeOutputActual(input);
                                }
                                break;
                            }
        }
    } else {
        removeOutputWire(bc);
        bc->removeInputWire(this);
        std::vector<Connection> connections;
        bc->scanComponents(connections);
        bool theSame = false;
        for (auto& c : connections)
            if (c.isOutput && c.component == this)
                theSame = true;
        if (!theSame) {
            for (auto& c : connections) {
                if (c.component->getComponent() == Peg)
                    c.component->removeInputActual(this);
                else {
                    if (!c.isOutput) {
                        if (!setup)
                            array.add(c.component);
                        removeOutputActual(c.component);
                        c.component->removeInputActual(this);
                    }
                }
            }
        }
    }
}

void BasicComponent::disconnectAll(Array& array) {
    uint8_t insAmount = wiredInAmount;
    uint8_t outsAmount = wiredOutAmount;
    BasicComponent** ins = new BasicComponent* [insAmount];
    BasicComponent** outs = new BasicComponent* [outsAmount];
    for (uint8_t i = 0; i < insAmount; i++) {
        ins[i] = getWiredIn(i);
    }
    for (uint8_t i = 0; i < outsAmount; i++) {
        outs[i] = getWiredOut(i);
    }
    for (uint8_t i = 0; i < insAmount; i++) {
        if (ins[i]->isWiredOutput(this))
            ins[i]->disconnect(this, false, array, false);
        else
            disconnect(ins[i], true, array, false);
    }
    for (uint8_t i = 0; i < outsAmount; i++) {
        disconnect(outs[i], false, array, false);
    }
    delete[] ins;
    delete[] outs;
    array.deleteComponent(this);
}

sf::Vector2<uint8_t> BasicComponent::getPosition() const {
    return sf::Vector2<uint8_t>((uint8_t) 0b1111 & position, (uint8_t) ((uint8_t) 0b11110000 & position) >> (uint8_t) 4);
}

bool BasicComponent::isConnected(BasicComponent* bc, bool in) {
    if (in) {
        bool t1 = false, t2 = false;
        for (uint8_t i = 0; i < wiredInAmount; i++) {
            if (getWiredIn(i) == bc) {
                t1 = true;
            }
        }
        for (uint8_t i = 0; i < bc->getWiredInAmount(); i++) {
            if (bc->getWiredIn(i) == this) {
                t2 = true;
            }
        }
        return t1 && t2;
    } else {
        return isWiredOutput(bc);
    }
}

Rotation BasicComponent::getRotation() const {
    return Rotation(data & 0b11u);
}

void BasicComponent::setRotation(Rotation rotation) {
    data = (data & 0b11111100u) | (uint8_t) rotation;
}

void BasicComponent::drawPreviewTexture(sf::RenderWindow* window, sf::Vector2f position, Rotation rotation) {
    sf::Texture texture;
    sf::Texture texture1;
    sf::Sprite bodySprite = getBodySprite(&texture);
    sf::Sprite pegsSprite = getPegsSprite(&texture1, sf::Color::Black, sf::Color::Black);
    bodySprite.setPosition(position + sf::Vector2f(5.5f, 5.5f));
    pegsSprite.setPosition(position + sf::Vector2f(5.5f, 5.5f));
    bodySprite.setColor(sf::Color(255, 255, 255, 100));
    pegsSprite.setColor(sf::Color(255, 255, 255, 100));
    bodySprite.setRotation((float) rotation * 90);
    pegsSprite.setRotation((float) rotation * 90);
    window->draw(bodySprite);
    window->draw(pegsSprite);
}

Component BasicComponent::getComponent() {
    return Nothing;
}

//void BasicComponent::drawBody(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale)
//{
//    static sf::Texture texture;
//    static sf::Sprite sprite = getBodySprite(&texture);
//    uint16_t rotation = (0b11u & data) * 90;
//    sf::Vector2f position = sf::Vector2f(0b1111u & this->position, (0b11110000u & this->position) >> 4u) * 11.0f;
//    sprite.setRotation(rotation);
//    sprite.setScale(sf::Vector2f(scale, scale));
//    sf::Vector2f calcPos = fragmentPosition + (position + sf::Vector2f(5.5f, 5.5f)) * (float) scale;
//    sprite.setPosition(std::floor(calcPos.x), std::floor(calcPos.y));
//    window->draw(sprite);
//}

void BasicComponent::drawBody(sf::RenderWindow& window, sf::Vector2u fragmentPosition) {
    static sf::Sprite* sprite[Component::AMOUNT]{nullptr};
    Component thisComponent = getComponent();
    if (sprite[thisComponent] == nullptr) {
        sprite[thisComponent] = new sf::Sprite(getBodySprite(new sf::Texture));
    }
    uint16_t rotation = (0b11u & data) * 90;
    sf::Vector2f position = sf::Vector2f(0b1111u & this->position, (0b11110000u & this->position) >> 4u) * 11.0f;
    sprite[thisComponent]->setRotation(rotation);
    sf::Vector2f calcPos = (sf::Vector2f) (fragmentPosition * 16u * 11u) + (position + sf::Vector2f(5.5f, 5.5f));
    sprite[thisComponent]->setPosition(calcPos.x, calcPos.y);
    window.draw(*sprite[thisComponent]);
}

void BasicComponent::drawWires(sf::RenderWindow& window, sf::Vector2u fragmentPosition) {
    for (uint8_t i = 0; i < wiredOutAmount; i++) {
        sf::Vector2i fragmentDifference = (sf::Vector2i) (getWiredOut(i)->getFragmentPosition() - this->fragmentPosition);
        
        fragmentDifference.x = fragmentDifference.x > 128 ? fragmentDifference.x - 256 : fragmentDifference.x;
        fragmentDifference.x = fragmentDifference.x <= -128 ? fragmentDifference.x + 256 : fragmentDifference.x;
        fragmentDifference.y = fragmentDifference.y > 128 ? fragmentDifference.y - 256 : fragmentDifference.y;
        fragmentDifference.y = fragmentDifference.y <= -128 ? fragmentDifference.y + 256 : fragmentDifference.y;
        sf::Vector2f inputPoint = getWiredOut(i)->getInputPoint() + (sf::Vector2f) (fragmentPosition * 16u * 11u);
        sf::Vector2f outputPoint = getOutputPoint() + (sf::Vector2f) (fragmentPosition * 16u * 11u);
        sfLine sfline(sf::Vector2f(inputPoint.x + (fragmentDifference.x * 16.0f * 11.0f),
                                   inputPoint.y + (fragmentDifference.y * 16.0f * 11.0f)), outputPoint, getState() ? sf::Color::Red : sf::Color::Black, 1);
        sfline.draw(window);
    }
    for (uint8_t i = 0; i < wiredInAmount; i++) {
        sf::Vector2i fragmentDifference = (sf::Vector2i) (getWiredIn(i)->getFragmentPosition() - this->fragmentPosition);
        fragmentDifference.x = fragmentDifference.x > 128 ? fragmentDifference.x - 256 : fragmentDifference.x;
        fragmentDifference.x = fragmentDifference.x <= -128 ? fragmentDifference.x + 256 : fragmentDifference.x;
        fragmentDifference.y = fragmentDifference.y > 128 ? fragmentDifference.y - 256 : fragmentDifference.y;
        fragmentDifference.y = fragmentDifference.y <= -128 ? fragmentDifference.y + 256 : fragmentDifference.y;
        sf::Vector2f first = (getWiredIn(i)->isWiredOutput(this) ? getWiredIn(i)->getOutputPoint() : getWiredIn(i)->getInputPoint()) + (sf::Vector2f) (fragmentPosition * 16u * 11u);
        first += (sf::Vector2f) (fragmentDifference * 16 * 11);
        sf::Vector2f second = getInputPoint() + (sf::Vector2f) (fragmentPosition * 16u * 11u);
        sfLine sfline(first, second, getInput() ? sf::Color::Red : sf::Color::Black, 1);
        sfline.draw(window);
    }
}

void BasicComponent::drawPegs(sf::RenderWindow& window, sf::Vector2u fragmentPosition) {
    static sf::Sprite* sprite[Component::AMOUNT][4]{nullptr};
    Component thisComponent = getComponent();
    if (sprite[thisComponent][0] == nullptr) {
        sprite[thisComponent][0] = new sf::Sprite(getPegsSprite(new sf::Texture, sf::Color::Black, sf::Color::Black));
        sprite[thisComponent][1] = new sf::Sprite(getPegsSprite(new sf::Texture, sf::Color::Black, sf::Color::Red));
        sprite[thisComponent][2] = new sf::Sprite(getPegsSprite(new sf::Texture, sf::Color::Red, sf::Color::Black));
        sprite[thisComponent][3] = new sf::Sprite(getPegsSprite(new sf::Texture, sf::Color::Red, sf::Color::Red));
    }
    uint16_t rotation = (0b11u & data) * 90;
    uint8_t state = (0b11000u & data) >> 3u;
    sf::Vector2f position = sf::Vector2f(0b1111u & this->position, (0b11110000u & this->position) >> 4u) * 11.0f;
    sprite[thisComponent][state]->setRotation(rotation);
    sf::Vector2f calcPos = (sf::Vector2f) (fragmentPosition * 16u * 11u) + (position + sf::Vector2f(5.5f, 5.5f));
    sprite[thisComponent][state]->setPosition(calcPos.x, calcPos.y);
    window.draw(*sprite[thisComponent][state]);
}

bool BasicComponent::isWiredOutput(BasicComponent* basicComponent) const {
    for (uint8_t i = 0; i < wiredOutAmount; i++)
        if (getWiredOut(i) == basicComponent)
            return true;
    return false;
}

sf::Vector2f BasicComponent::getInputPoint() {
    return sf::Vector2f();
}

sf::Vector2f BasicComponent::getOutputPoint() {
    return sf::Vector2f();
}

sf::IntRect BasicComponent::getBodyRectangle(sf::Vector2u componentPosition) {
    return sf::IntRect();
}

sf::IntRect BasicComponent::getInputRectangle(sf::Vector2u componentPosition) {
    return sf::IntRect();
}

sf::IntRect BasicComponent::getOutputRectangle(sf::Vector2u componentPosition) {
    return sf::IntRect();
}

sf::Sprite BasicComponent::getBodySprite(sf::Texture* texture) {
    return sf::Sprite();
}

sf::Sprite BasicComponent::getPegsSprite(sf::Texture* texture, sf::Color in, sf::Color out) {
    return sf::Sprite();
}

void BasicComponent::update() {}


#pragma clang diagnostic pop
