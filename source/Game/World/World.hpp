#ifndef GAME_WORLD_HPP
#define GAME_WORLD_HPP


#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <thread>
#include <chrono>
#include "../Rotation.hpp"
#include "Chunk/Chunk.hpp"
#include "Fragment/Fragment.hpp"
#include "Components/BasicComponent.hpp"
#include "UpdateThread/Array/Array.hpp"

class UpdateThread;

#include "UpdateThread/UpdateThread.hpp"
#include "Components/ComponentData.hpp"

class World {
        friend UpdateThread;
    private:
        static const int WORLD_SIZE = 16 * 16;
        Chunk* chunks[WORLD_SIZE]{};
        std::mutex worldChangeMutex;
    public:
        
        UpdateThread updateThread;
        static sf::Vector2u getChunk(sf::Vector2u position);
        static uint32_t getAbsolute(sf::Vector2u chunk);
        static sf::Vector2u getFragmentRelativePosition(uint32_t absolute);
        static sf::Vector2u getChunkRelativePosition(sf::Vector2u position);
        World();
        ~World();
        
        void addComponent(Component component, sf::Vector2u position, ComponentData componentData, bool setup);
        void removeComponent(sf::Vector2u position);
        void logicStart();
        void logicResume();
        void logicPause();
        void logicStop();
        Fragment* getFragmentFromPoint(sf::Vector2u point);
        BasicComponent* getComponent(sf::Vector2u componentPosition);
        void connect(sf::Vector2u from, sf::Vector2u to, bool in, bool setup);
        void disconnect(sf::Vector2u from, sf::Vector2u to, bool in, bool setup);
        bool isConnected(sf::Vector2u from, sf::Vector2u to, bool in = false);
        void fullTick(Array& array);
        void draw(sf::RenderWindow& window);
};


#endif //GAME_WORLD_HPP
