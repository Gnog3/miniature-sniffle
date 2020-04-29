#ifndef GAME_BLOTTER_HPP
#define GAME_BLOTTER_HPP

#include "../BasicComponent.hpp"
#include "../Component.hpp"
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

class Blotter : public BasicComponent
{
    private:
        sf::Sprite getSprite(sf::Texture *texture, sf::Color in, sf::Color out) override;

    public:

        Blotter(sf::Vector2u position, uint8_t rotation);

        void update() override;

        void draw(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale) override;
};


#endif //GAME_BLOTTER_HPP
