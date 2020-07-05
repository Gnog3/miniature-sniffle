#include <iostream>

#include "World.hpp"
#include "Components/ComponentData.hpp"


sf::Vector2u World::getChunk(sf::Vector2u position) {
    return position / 4096u;
}

uint32_t World::getAbsolute(sf::Vector2u chunk) {
    return chunk.y * 16 + chunk.x;
}

sf::Vector2u World::getFragmentRelativePosition(uint32_t absolute) {
    uint32_t y = absolute / 16;
    uint32_t x = absolute % 16;
    return sf::Vector2u(x, y);
}

sf::Vector2u World::getChunkRelativePosition(sf::Vector2u position) {
    position.x %= 4096;
    position.y %= 4096;
    return position;
}

World::World() {
    for (int i = 0; i < WORLD_SIZE; i++) {
        //chunks[i] = new Chunk((sf::Vector2<int8_t>)getFragmentRelativePosition(i));
        chunks[i] = nullptr;
    }
}

World::~World() {
    updateThread.logicStop();
}


void World::addComponent(Component component, sf::Vector2u position, ComponentData componentData, bool setup) {
    sf::Vector2u chunk = getChunk(position);
    uint32_t absolute = getAbsolute(chunk);
    if (chunks[absolute] == nullptr) {
        chunks[absolute] = new Chunk((sf::Vector2<uint8_t>) chunk);
    }
    
    chunks[absolute]->addComponent(component, getChunkRelativePosition(position), componentData, *updateThread.array, setup);
}

void World::removeComponent(sf::Vector2u position) {
    sf::Vector2u chunk = getChunk(position);
    
    uint32_t absolute = getAbsolute(chunk);
    
    bool isEmpty = chunks[absolute]->removeComponent(getChunkRelativePosition(position), *updateThread.array);
    
    if (isEmpty) {
        delete chunks[absolute];
        chunks[absolute] = nullptr;
    }
}

void World::logicStart() {
    updateThread.logicLaunch(*this);
}

void World::logicResume() {
    updateThread.logicResume();
}

void World::logicPause() {
    updateThread.logicPause();
}

void World::logicStop() {
    updateThread.logicStop();
}

Fragment* World::getFragmentFromPoint(sf::Vector2u point) {
    uint32_t absolute = getAbsolute(getChunk(point));
    if (chunks[absolute] == nullptr)
        return nullptr;
    return chunks[getAbsolute(getChunk(point))]->getFragment(getChunkRelativePosition(point));
}

BasicComponent* World::getComponent(sf::Vector2u componentPosition) {
    uint32_t absolute = getAbsolute(getChunk(componentPosition));
    if (chunks[absolute] == nullptr) {
        return nullptr;
    }
    return chunks[absolute]->getComponent(getChunkRelativePosition(componentPosition));
}

void World::connect(sf::Vector2u from, sf::Vector2u to, bool in, bool setup) {
    BasicComponent* first = getComponent(from);
    BasicComponent* second = getComponent(to);
    if (in) {
        if (first->isConnected(second, false) || second->isConnected(first, false))
            return;
    } else {
        if (first->isConnected(second, true))
            return;
    }
    first->connect(second, in, *updateThread.array, setup);
}

void World::disconnect(sf::Vector2u from, sf::Vector2u to, bool in, bool setup) {
    BasicComponent* first = getComponent(from);
    BasicComponent* second = getComponent(to);
    
    first->disconnect(second, in, *updateThread.array, setup);
}

bool World::isConnected(sf::Vector2u from, sf::Vector2u to, bool in) {
    BasicComponent* first = getComponent(from);
    BasicComponent* second = getComponent(to);
    
    return first->isConnected(second, in);
}

void World::fullTick(Array& array) {
    for (auto& chunk : chunks) {
        if (chunk != nullptr)
            chunk->calculateInputs();
    }
    for (auto& chunk : chunks) {
        if (chunk != nullptr)
            chunk->fullTick();
    }
    for (auto& chunk : chunks) {
        if (chunk != nullptr)
            chunk->shiftState(array);
    }
}

void World::draw(sf::RenderWindow& window) {
    sf::Vector2u resolution = window.getSize();
    sf::Vector2f screenTopLeftPoint = window.mapPixelToCoords(sf::Vector2i(0, 0));
    sf::Vector2f screenBottomRightPoint = window.mapPixelToCoords((sf::Vector2i) resolution);
    sf::Vector2u fromChunk = getChunk((sf::Vector2u) screenTopLeftPoint / 11u);
    sf::Vector2u toChunk = getChunk((sf::Vector2u) screenBottomRightPoint / 11u);
    void (Chunk::*func[])(sf::RenderWindow&){
            &Chunk::drawBody,
            &Chunk::drawWires,
            &Chunk::drawPegs
    };
    for (auto& function : func) {
        for (uint32_t y = fromChunk.y; y <= toChunk.y; y++) {
            for (uint32_t x = fromChunk.x; x <= toChunk.x; x++) {
                uint32_t absolute = getAbsolute(sf::Vector2u(x, y));
                if (chunks[absolute] != nullptr) {
                    if (function == &Chunk::drawBody) {
                        sf::Vector2u chunkBorderPosition(x, y);
                        sf::RectangleShape chunkBorder(sf::Vector2f(4096 * 11, 4096 * 11));
                        chunkBorder.setOutlineColor(sf::Color::Red);
                        chunkBorder.setFillColor(sf::Color::Transparent);
                        chunkBorder.setOutlineThickness(-3);
                        chunkBorder.setPosition((float) x * 4096 * 11, (float) y * 4096 * 11);
                        //window->draw(chunkBorder);
                    }
                    (chunks[absolute]->*function)(window);
                }
            }
        }
    }
}
