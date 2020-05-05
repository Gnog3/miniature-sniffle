#ifndef GAME_PEG_HPP
#define GAME_PEG_HPP


#include "../BasicComponent.hpp"

class Peg : public BasicComponent
{
    private:
        sf::Sprite getBodySprite(sf::Texture* texture) override;

        sf::Sprite getPegsSprite(sf::Texture* texture, sf::Color in, sf::Color out) override;
    public:
        Peg(sf::Vector2<uint8_t> position, sf::Vector2<uint8_t> fragmentPosition);

        bool isPeg() override;

        sf::Vector2f getInputPoint() override;

        sf::Vector2f getOutputPoint() override;

        void drawBody(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale) override;

        void drawWires(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale) override;

        void drawPegs(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale) override;
};


#endif //GAME_PEG_HPP
