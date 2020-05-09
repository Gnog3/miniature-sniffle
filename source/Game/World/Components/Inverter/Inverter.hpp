#ifndef GAME_INVERTER_HPP
#define GAME_INVERTER_HPP

#include "../BasicComponent.hpp"
#include "../Component.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Inverter : public BasicComponent
{
    private:
        sf::Sprite getBodySprite(sf::Texture* texture) override;
        
        sf::Sprite getPegsSprite(sf::Texture* texture, sf::Color in, sf::Color out) override;
    
    public:
        Inverter();
        Inverter(sf::Vector2<uint8_t> position, sf::Vector2<uint8_t> fragmentPosition, uint8_t rotation);
        sf::Vector2f getInputPoint() override;
        sf::Vector2f getOutputPoint() override;
        sf::IntRect getBodyRectangle(sf::Vector2i componentPosition) override;
        sf::IntRect getInputRectangle(sf::Vector2i componentPosition) override;
        sf::IntRect getOutputRectangle(sf::Vector2i componentPosition) override;
        void update() override;
        void drawBody(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale) override;
        void drawPegs(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale) override;
};


#endif //GAME_INVERTER_HPP