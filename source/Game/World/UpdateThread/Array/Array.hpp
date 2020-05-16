#ifndef GAME_ARRAY_HPP
#define GAME_ARRAY_HPP
#define INIT_ARRAY_SIZE 131072

#include <cstdint>
#include <mutex>
#include <cstring>
#include <iostream>

class BasicComponent;


class Array
{
    private:
        
        BasicComponent** array[2]{nullptr};
        //std::mutex mutex;
        uint32_t amountNext = 0;
        uint32_t amountCurrent = 0;
        uint32_t getCurrent = 0;
        uint32_t maxNext = INIT_ARRAY_SIZE;
        uint32_t maxCurrent = INIT_ARRAY_SIZE;
    public:
        Array();
        ~Array();
        
        void deleteComponent(BasicComponent* basicComponent);
        void replaceComponent(BasicComponent* from, BasicComponent* to);
        
        inline BasicComponent* getNext()
        {
            //std::lock_guard<std::mutex> lg(mutex);
            getCurrent++;
            return (getCurrent - 1) < amountCurrent ? array[0][getCurrent - 1] : nullptr;
        }
        
        inline void add(BasicComponent* basicComponent)
        {
            //mutex.lock();
            if (amountNext == maxNext)
            {
                maxNext += INIT_ARRAY_SIZE;
                BasicComponent** newArray = new BasicComponent* [maxNext];
                std::memcpy(newArray, array[1], sizeof(nullptr) * (maxNext - INIT_ARRAY_SIZE));
                delete[] array[1];
                array[1] = newArray;
                //std::cout << "You're stupid" << std::endl;
            }
            array[1][amountNext++] = basicComponent;
            //mutex.unlock();
        }
        
        inline void shift()
        {
            BasicComponent** t = array[0];
            array[0] = array[1];
            array[1] = t;
            if (maxCurrent > INIT_ARRAY_SIZE)
            {
                delete[] array[1];
                array[1] = new BasicComponent* [INIT_ARRAY_SIZE];
            }
            maxCurrent = maxNext;
            maxNext = INIT_ARRAY_SIZE;
            amountCurrent = amountNext;
            amountNext = 0;
            getCurrent = 0;
        }
        
        inline void resetCurrent()
        {
            getCurrent = 0;
        }
};


#include "../../Components/BasicComponent.hpp"

#endif //GAME_ARRAY_HPP
