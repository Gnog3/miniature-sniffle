
#include "Fragment.hpp"


Fragment::Fragment(sf::Vector2<uint8_t> position) {
    componentList = nullptr;
    if (position.x > 100 || position.y > 100) {
        int a = 5;
        int b = 6;
    }
    this->position = position;
}

Fragment::~Fragment() {

}

uint16_t Fragment::getComponentAmount() {
    return componentAmount;
}

void Fragment::addComponent(Component component, sf::Vector2u position, ComponentData componentData, Array& array, bool setup) {
    componentAmount++;
    BasicComponent* newComponentList = new BasicComponent[componentAmount];
    if (componentList != nullptr) {
        //TODO: жесткий костыль, переделать нафиг все
        for (uint16_t i = 0; i < componentAmount - 1; i++) {
            std::memcpy(newComponentList + i, componentList + i, sizeof(BasicComponent));
            newComponentList[i].fixMove(&componentList[i], array, setup);
        }
        delete[] componentList;
    }
    componentList = newComponentList;
    
    
    switch (component) {
        case Component::Peg:
            new(&componentList[componentAmount - 1]) class Peg((sf::Vector2<uint8_t>) position, this->position);
            break;
        case Component::Inverter:
            new(&componentList[componentAmount - 1]) class Inverter((sf::Vector2<uint8_t>) position, this->position, (uint8_t) componentData);
            break;
        case Component::Blotter:
            new(&componentList[componentAmount - 1]) class Blotter((sf::Vector2<uint8_t>) position, this->position, (uint8_t) componentData);
            break;
        case Component::Switch:
            new(&componentList[componentAmount - 1]) class Switch((sf::Vector2<uint8_t>) position, this->position, (uint8_t) componentData);
            break;
    }
    if (!setup)
        array.add(&componentList[componentAmount - 1]);
}

bool Fragment::removeComponent(sf::Vector2u position, Array& array) {
    componentAmount--;
    if (componentAmount > 0) {
        BasicComponent* newComponentList = new BasicComponent[componentAmount];
        
        bool found = false;
        for (uint16_t i = 0; i < componentAmount + 1; i++) {
            if (!found && (sf::Vector2<uint8_t>) position == componentList[i].getPosition()) {
                found = true;
                componentList[i].disconnectAll(array);
                continue;
            }
            std::memcpy(newComponentList + i - (found ? 1 : 0), componentList + i, sizeof(BasicComponent));
            newComponentList[i - (found ? 1 : 0)].fixMove(&componentList[i], array, false);
        }
        delete[] componentList;
        componentList = newComponentList;
        return false;
    } else {
        componentList[0].disconnectAll(array);
        delete[] componentList;
        componentList = nullptr;
        return true;
    }
}

BasicComponent* Fragment::getComponent(sf::Vector2<uint8_t> position) {
    for (uint16_t i = 0; i < componentAmount; i++) {
        sf::Vector2<uint8_t> componentPosition = componentList[i].getPosition();
        if (componentPosition == position)
            return &componentList[i];
    }
    return nullptr;
}

BasicComponent* Fragment::getComponent(uint16_t id) {
    return &componentList[id];
}

void Fragment::calculateInputs() {
    for (uint16_t i = 0; i < componentAmount; i++) {
        componentList[i].calculateInput();
    }
}

void Fragment::fullTick() {
    for (uint16_t i = 0; i < componentAmount; i++) {
        componentList[i].update();
    }
}

void Fragment::shiftState(Array& array) {
    for (uint16_t i = 0; i < componentAmount; i++) {
        componentList[i].shiftState(array);
    }
}

void Fragment::drawFunc(sf::RenderWindow& window, sf::Vector2u chunkPosition, void (BasicComponent::*func)(sf::RenderWindow&, sf::Vector2u)) {
    sf::Vector2u fragmentPosition = chunkPosition * 256u + (sf::Vector2u) position;
    if (func == &BasicComponent::drawBody) {
        sf::RectangleShape fragmentBorder(sf::Vector2f(16 * 11, 16 * 11));
        fragmentBorder.setFillColor(sf::Color::Transparent);
        fragmentBorder.setOutlineColor(sf::Color::Blue);
        fragmentBorder.setOutlineThickness(-1.0f);
        fragmentBorder.setPosition((sf::Vector2f) (fragmentPosition * 16u * 11u));
        window.draw(fragmentBorder);
    }
    for (int i = 0; i < componentAmount; i++) {
        (componentList[i].*func)(window, fragmentPosition);
    }
}

void Fragment::drawBody(sf::RenderWindow& window, sf::Vector2u chunkPosition) {
    drawFunc(window, chunkPosition, &BasicComponent::drawBody);
}

void Fragment::drawWires(sf::RenderWindow& window, sf::Vector2u chunkPosition) {
    drawFunc(window, chunkPosition, &BasicComponent::drawWires);
}

void Fragment::drawPegs(sf::RenderWindow& window, sf::Vector2u chunkPosition) {
    drawFunc(window, chunkPosition, &BasicComponent::drawPegs);
}
