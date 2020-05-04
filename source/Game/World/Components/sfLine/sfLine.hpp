#ifndef GAME_SFLINE_HPP
#define GAME_SFLINE_HPP

#include <SFML/Graphics.hpp>
#include <ctgmath>

class sfLine : public sf::Drawable
{
    public:
        sfLine(const sf::Vector2f& point1, const sf::Vector2f& point2, sf::Color color, float thickness);
        void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates()) const;
    private:
        sf::Vertex vertices[4];
        float thickness;
        sf::Color color;
};


#endif //GAME_SFLINE_HPP
