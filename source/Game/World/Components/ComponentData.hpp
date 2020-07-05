#ifndef GAME_COMPONENTDATA_HPP
#define GAME_COMPONENTDATA_HPP

#include <cstdint>

enum class ComponentData : uint8_t {
        Up = 0b0,
        Right = 0b1,
        Down = 0b10,
        Left = 0b11,
        OutNextOn = 0b100,
        OutOn = 0b1000,
        InOn = 0b10000
};
#endif //GAME_COMPONENTDATA_HPP
