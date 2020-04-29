#ifndef GAME_INVERTER_HPP
#define GAME_INVERTER_HPP

#include "../BasicComponent.hpp"
#include "../Component.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class Inverter : public BasicComponent
{
    private:
        sf::Sprite getSprite(sf::Texture *texture, sf::Color in, sf::Color out) override;

    public:
        Inverter();

        Inverter(sf::Vector2u position, uint8_t rotation);

        void update() override;

        void draw(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale) override;
};


#endif //GAME_INVERTER_HPP