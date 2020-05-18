#include "UpdateThread.hpp"

void UpdateThread::main(World& world)
{
    world.fullTick(*array);
    while (!requireStop)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        while (requirePause)
        {
            isPaused = true;
            if (requireStop)
                break;
        }
        
        isPaused = false;
        array->shift();
        
        BasicComponent* componentToHandle;
        
        while ((componentToHandle = array->getNext()) != nullptr)
        {
            componentToHandle->calculateInput();
        }
        
        array->resetCurrent();
        
        while ((componentToHandle = array->getNext()) != nullptr)
            componentToHandle->update();
        
        array->resetCurrent();
        
        while ((componentToHandle = array->getNext()) != nullptr)
            componentToHandle->shiftState(*array);
        
        ups++;
    }
}

UpdateThread::~UpdateThread()
{
    delete thread;
}

void UpdateThread::logicLaunch(World& world)
{
    thread = new std::thread(
            [this, &world]()
            {
                this->main(world);
            });
}

void UpdateThread::logicResume()
{
    requirePause = false;
}

void UpdateThread::logicPause()
{
    requirePause = true;
    while (!isPaused);
}

void UpdateThread::logicStop()
{
    requireStop = true;
    thread->join();
}

uint32_t UpdateThread::getUps() const
{
    return ups;
}

void UpdateThread::resetUps(World& world)
{
    logicPause();
    ups = 0;
    upsClock.restart();
    logicResume();
}
