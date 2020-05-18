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

class World
{
        friend UpdateThread;
    private:
        static const int WORLD_SIZE = 16 * 16;
        Chunk* chunks[WORLD_SIZE]{};
        std::mutex worldChangeMutex;
    public:
        
        UpdateThread updateThread;
        static sf::Vector2i getChunk(sf::Vector2i position);
        static uint32_t getAbsolute(sf::Vector2i chunk);
        static sf::Vector2i getRelative(uint32_t absolute);
        World();
        ~World();
        static sf::Vector2u handlePosition(sf::Vector2i position);
        void addComponent(Component component, sf::Vector2i position, ComponentData componentData, bool setup);
        void removeComponent(sf::Vector2i position);
        void logicStart();
        void logicResume();
        void logicPause();
        void logicStop();
        Fragment* getFragmentFromPoint(sf::Vector2i point);
        BasicComponent* getComponent(sf::Vector2i componentPosition);
        void connect(sf::Vector2i from, sf::Vector2i to, bool in, bool setup);
        void disconnect(sf::Vector2i from, sf::Vector2i to, bool in, bool setup);
        bool isConnected(sf::Vector2i from, sf::Vector2i to, bool in = false);
        void fullTick(Array& array);
        void draw(sf::RenderWindow* window, sf::Vector2f playerPosition, uint8_t scale);
};


#endif //GAME_WORLD_HPP
