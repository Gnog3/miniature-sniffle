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
        Inverter(sf::Vector2<uint8_t> position, sf::Vector2<uint8_t> fragmentPosition, uint8_t rotation);

        void update() override;

        void draw(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale) override;
};


#endif //GAME_INVERTER_HPP