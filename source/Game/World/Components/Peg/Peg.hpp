#ifndef GAME_PEG_HPP
#define GAME_PEG_HPP


#include "../BasicComponent.hpp"

class Peg : public BasicComponent
{
    private:
        sf::Sprite getSprite(sf::Texture *texture, sf::Color in, sf::Color out) override;

    public:
        Peg();

        Peg(sf::Vector2u position, uint8_t rotation);

        void update() override;

        void draw(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale) override;
};


#endif //GAME_PEG_HPP
