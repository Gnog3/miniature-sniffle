#ifndef GAME_BLOTTER_HPP
#define GAME_BLOTTER_HPP

#include "../BasicComponent.hpp"
#include "../Component.hpp"
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

class Blotter : public BasicComponent
{
    private:
        sf::Sprite getBodySprite(sf::Texture* texture) override;

    public:
        Blotter(sf::Vector2<uint8_t> position, sf::Vector2<uint8_t> fragmentPosition, uint8_t rotation);

        void update() override;
};


#endif //GAME_BLOTTER_HPP
