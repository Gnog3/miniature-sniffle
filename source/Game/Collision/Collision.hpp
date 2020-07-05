#ifndef GAME_COLLISION_HPP
#define GAME_COLLISION_HPP

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <cstdint>

class Collision {
    public:
        static bool polyPoly(const std::vector<sf::Vector2f>& p1, const std::vector<sf::Vector2f>& p2);
        
        static bool polyLine(const std::vector<sf::Vector2f>& vertices, sf::Vector2f point1, sf::Vector2f point2);
        
        static bool lineLine(sf::Vector2f point1, sf::Vector2f point2, sf::Vector2f point3, sf::Vector2f point4);
};


#endif //GAME_COLLISION_HPP
