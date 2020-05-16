#include "UpdateThread.hpp"

void UpdateThread::main(World& world)
{
    uint64_t amount = 0;
    sf::Clock clock;
    world.fullTick(*array);
    while (!requireStop)
    {
        //std::this_thread::sleep_for(std::chrono::milliseconds(1));
        while (!world.worldChangeMutex.try_lock());
        array->shift();
        
        BasicComponent* componentToHandle;
//        if (world.getComponent(sf::Vector2i(0, 0)) != nullptr)
//            array.add(world.getComponent(sf::Vector2i(0, 0)));
        
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
    
        amount++;
    
        
        if (clock.getElapsedTime().asMilliseconds() >= 1000)
        {
            //std::cout << amount << std::endl;
            ups = amount;
            amount = 0;
            clock.restart();
        }
        world.worldChangeMutex.unlock();
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

}

void UpdateThread::logicPause()
{

}

void UpdateThread::logicStop()
{
    requireStop = true;
    thread->join();
}


