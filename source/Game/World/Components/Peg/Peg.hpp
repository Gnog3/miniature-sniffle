#ifndef GAME_PEG_HPP
#define GAME_PEG_HPP


#include "../BasicComponent.hpp"

class Peg : public BasicComponent {
    private:
        sf::Sprite getBodySprite(sf::Texture* texture) override;
        sf::Sprite getPegsSprite(sf::Texture* texture, sf::Color in, sf::Color out) override;
    public:
        Peg();
        Peg(sf::Vector2<uint8_t> position, sf::Vector2<uint8_t> fragmentPosition);
        Component getComponent() override;
        sf::Vector2f getInputPoint() override;
        sf::IntRect getBodyRectangle(sf::Vector2u componentPosition) override;
        sf::IntRect getInputRectangle(sf::Vector2u componentPosition) override;
        sf::IntRect getOutputRectangle(sf::Vector2u componentPosition) override;
        void drawWires(sf::RenderWindow& window, sf::Vector2u fragmentPosition) override;
};


#endif //GAME_PEG_HPP
