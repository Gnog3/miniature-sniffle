#include "Chunk.hpp"
#include "../UpdateThread/Array/Array.hpp"

uint32_t Chunk::getAbsolute(sf::Vector2u fragment) {
    return fragment.y * 256 + fragment.x;
}

sf::Vector2u Chunk::getRelative(uint32_t absolute) {
    return sf::Vector2u(absolute % 256, absolute / 256);
}

sf::Vector2u Chunk::getFragmentPosition(sf::Vector2u position) {
    return position / 16u;
}

Chunk::Chunk(sf::Vector2<uint8_t> position) {
    this->position = position;
    for (int i = 0; i < CHUNK_SIZE; i++) {
        sf::Vector2u fragment = getRelative(i);
        //fragments[i] = new Fragment(sf::Vector2<uint8_t>(fragment));
        fragments[i] = nullptr;
    }
}

void Chunk::addComponent(Component component, sf::Vector2u position, ComponentData componentData, Array& array, bool setup) {
    sf::Vector2u fragment = position / 16u;
    uint32_t absolute = getAbsolute(fragment);
    if (fragments[absolute] == nullptr) {
        fragments[absolute] = new Fragment(sf::Vector2<uint8_t>(fragment));
        active++;
    }
    
    position.x %= 16;
    position.y %= 16;
    fragments[absolute]->addComponent(component, position, componentData, array, setup);
    
}

bool Chunk::removeComponent(sf::Vector2u position, Array& array) {
    sf::Vector2u fragment = position / 16u;
    uint32_t absolute = getAbsolute(fragment);
    position.x %= 16;
    position.y %= 16;
    bool isEmpty = fragments[absolute]->removeComponent(position, array);
    if (isEmpty) {
        active--;
        delete fragments[absolute];
        fragments[absolute] = nullptr;
        return active == 0;
    }
    return false;
}

Fragment* Chunk::getFragment(sf::Vector2u position) {
    return fragments[getAbsolute(getFragmentPosition(position))];
}

BasicComponent* Chunk::getComponent(sf::Vector2u componentPosition) {
    uint32_t absolute = getAbsolute(componentPosition / 16u);
    if (fragments[absolute] == nullptr) {
        return nullptr;
    }
    componentPosition.x %= 16;
    componentPosition.y %= 16;
    return fragments[absolute]->getComponent((sf::Vector2<uint8_t>) componentPosition);
}

void Chunk::calculateInputs() {
    for (auto& fragment : fragments) {
        if (fragment != nullptr)
            fragment->calculateInputs();
    }
}

void Chunk::fullTick() {
    for (auto& fragment : fragments) {
        if (fragment != nullptr)
            fragment->fullTick();
    }
}

void Chunk::shiftState(Array& array) {
    for (auto& fragment : fragments) {
        if (fragment != nullptr)
            fragment->shiftState(array);
    }
}

void Chunk::drawFunc(sf::RenderWindow& window, void (Fragment::* func)(sf::RenderWindow&, sf::Vector2u)) {
    sf::Vector2f screenFirstPoint = window.mapPixelToCoords(sf::Vector2i(0, 0));
    sf::Vector2f screenLastPoint = window.mapPixelToCoords((sf::Vector2i) window.getSize());
    sf::Vector2f chunkFirstPoint = (sf::Vector2f) position * 4096.0f * 11.0f;
    sf::Vector2f chunkLastPoint = chunkFirstPoint + sf::Vector2f(4096.0f * 11.0f, 4096.0f * 11.0f);
    sf::Vector2f intersectionFirstPoint = sf::Vector2f(std::max(screenFirstPoint.x, chunkFirstPoint.x),
                                                       std::max(screenFirstPoint.y, chunkFirstPoint.y));
    sf::Vector2f intersectionLastPoint = sf::Vector2f(std::min(screenLastPoint.x, chunkLastPoint.x),
                                                      std::min(screenLastPoint.y, chunkLastPoint.y));
    sf::Vector2u firstFragment = getFragmentPosition((sf::Vector2u) intersectionFirstPoint / 11u);
    sf::Vector2u lastFragment = getFragmentPosition((sf::Vector2u) intersectionLastPoint / 11u);
    if (func == &Fragment::drawBody) {
        sf::RectangleShape chunkBorder(sf::Vector2f(4096 * 11, 4096 * 11));
        chunkBorder.setFillColor(sf::Color::Transparent);
        chunkBorder.setOutlineColor(sf::Color::Red);
        chunkBorder.setOutlineThickness(-3.0f);
        chunkBorder.setPosition(chunkFirstPoint);
        window.draw(chunkBorder);
    }
    for (uint32_t y = firstFragment.y; y <= lastFragment.y; ++y) {
        for (uint32_t x = firstFragment.x; x <= lastFragment.x; ++x) {
            uint16_t absolute = getAbsolute(sf::Vector2u(x % 256, y % 256));
            if (fragments[absolute] != nullptr) {
                (fragments[absolute]->*func)(window, (sf::Vector2u) position);
            }
        }
    }
}

void Chunk::drawBody(sf::RenderWindow& window) {
    drawFunc(window, &Fragment::drawBody);
}

void Chunk::drawWires(sf::RenderWindow& window) {
    drawFunc(window, &Fragment::drawWires);
}

void Chunk::drawPegs(sf::RenderWindow& window) {
    drawFunc(window, &Fragment::drawPegs);
}

