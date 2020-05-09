
#include "Collision.hpp"

bool Collision::polyPoly(const std::vector<sf::Vector2f>& p1, const std::vector<sf::Vector2f>& p2)
{
    uint32_t next = 0;
    for (uint32_t current = 0; current < p1.size(); current++)
    {
        next = current + 1;
        if (next == p1.size())
            next = 0;
        if (polyLine(p2, p1[current], p1[next]))
            return true;
    }
    return false;
}

bool Collision::polyLine(const std::vector<sf::Vector2f>& vertices, sf::Vector2f point1, sf::Vector2f point2)
{
    uint32_t next = 0;
    for (uint32_t current = 0; current < vertices.size(); current++)
    {
        next = current + 1;
        if (next == vertices.size())
            next = 0;
        sf::Vector2f point3 = vertices[current];
        sf::Vector2f point4 = vertices[next];
        bool hit = lineLine(point1, point2, point3, point4);
        if (hit)
            return true;
    }
    return false;
}

bool Collision::lineLine(sf::Vector2f point1, sf::Vector2f point2, sf::Vector2f point3, sf::Vector2f point4)
{
    float uA = ((point4.x - point3.x) * (point1.y - point3.y) - (point4.y - point3.y) * (point1.x - point3.x)) / ((point4.y - point3.y) * (point2.x - point1.x) - (point4.x - point3.x) * (point2.y - point1.y));
    float uB = ((point2.x - point1.x) * (point1.y - point3.y) - (point2.y - point1.y) * (point1.x - point3.x)) / ((point4.y - point3.y) * (point2.x - point1.x) - (point4.x - point3.x) * (point2.y - point1.y));
    return uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1;
}


