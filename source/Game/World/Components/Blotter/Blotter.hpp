#ifndef GAME_BLOTTER_HPP
#define GAME_BLOTTER_HPP

#include "../BasicComponent.hpp"
#include "../Component.hpp"
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

class Blotter : public BasicComponent {
    private:
        sf::Sprite getBodySprite(sf::Texture* texture) override;
        
        sf::Sprite getPegsSprite(sf::Texture* texture, sf::Color in, sf::Color out) override;
    public:
        Blotter();
        Blotter(sf::Vector2<uint8_t> position, sf::Vector2<uint8_t> fragmentPosition, uint8_t rotation);
        Component getComponent() override;
        sf::Vector2f getInputPoint() override;
        sf::Vector2f getOutputPoint() override;
        sf::IntRect getBodyRectangle(sf::Vector2u componentPosition) override;
        sf::IntRect getInputRectangle(sf::Vector2u componentPosition) override;
        sf::IntRect getOutputRectangle(sf::Vector2u componentPosition) override;
        void update() override;
};


#endif //GAME_BLOTTER_HPP
