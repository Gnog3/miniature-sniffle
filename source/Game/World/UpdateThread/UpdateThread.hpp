#ifndef GAME_UPDATETHREAD_HPP
#define GAME_UPDATETHREAD_HPP

#include <thread>
#include "../Components/BasicComponent.hpp"
#include "Array/Array.hpp"
class World;

class UpdateThread
{
    private:
        std::thread* thread;
        void main(World& world);
        bool requireStop = false;
    public:
        Array* array = new Array;
        uint32_t ups = 0;
        ~UpdateThread();
        void logicLaunch(World& world);
        void logicResume();
        void logicPause();
        void logicStop();
};

#include "../World.hpp"

#endif //GAME_UPDATETHREAD_HPP
