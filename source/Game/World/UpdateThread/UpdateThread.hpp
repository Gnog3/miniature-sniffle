#ifndef GAME_UPDATETHREAD_HPP
#define GAME_UPDATETHREAD_HPP

#include <thread>
#include "../Components/BasicComponent.hpp"
#include "Array/Array.hpp"

class World;

class UpdateThread {
    private:
        std::thread* thread;
        void main(World& world);
        volatile bool requireStop = false;
        volatile bool requirePause = false;
        volatile bool isPaused = false;
        volatile uint64_t ups = 0;
    public:
        sf::Clock upsClock;
        Array* array = new Array;
        ~UpdateThread();
        void logicLaunch(World& world);
        void logicResume();
        void logicPause();
        void logicStop();
        uint32_t getUps() const;
        void resetUps(World& world);
};

#include "../World.hpp"

#endif //GAME_UPDATETHREAD_HPP
