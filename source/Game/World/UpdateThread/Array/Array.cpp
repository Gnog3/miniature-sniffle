#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"

#include "Array.hpp"

Array::Array()
{
    array[0] = new BasicComponent* [INIT_ARRAY_SIZE];
    array[1] = new BasicComponent* [INIT_ARRAY_SIZE];
}

Array::~Array()
{
    delete[] array[0];
    delete[] array[1];
}

void Array::deleteComponent(BasicComponent* basicComponent)
{
    if (amountNext > 1)
    {
        uint32_t shift = 0;
        for (uint32_t i = 0; i < amountNext; i++)
        {
            if (array[1][i] == basicComponent)
            {
                shift++;
                continue;
            }
            array[1][i - shift] = array[1][i];
        }
        amountNext -= shift;
    } else if (amountNext == 1)
    {
        if (array[1][0] == basicComponent)
            amountNext--;
    }
}

void Array::replaceComponent(BasicComponent* from, BasicComponent* to)
{
    for (uint32_t i = 0; i < amountNext; i++)
        if (array[1][i] == from)
            array[1][i] = to;
}

#pragma clang diagnostic pop