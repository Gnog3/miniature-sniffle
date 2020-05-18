#ifndef GAME_SWITCH_HPP
#define GAME_SWITCH_HPP
#include <SFML/Graphics.hpp>
#include "../Component.hpp"
#include "../BasicComponent.hpp"

class Switch : public BasicComponent
{
    private:
        sf::Sprite getBodySprite(sf::Texture* texture) override;
        sf::Sprite getPegsSprite(sf::Texture* texture, sf::Color in, sf::Color out) override;
    
    public:
        Switch();
        Switch(sf::Vector2<uint8_t> position, sf::Vector2<uint8_t> fragmentPosition, uint8_t componentData);
        Component getComponent() override;
        sf::Vector2f getOutputPoint() override;
        sf::IntRect getBodyRectangle(sf::Vector2i componentPosition) override;
        sf::IntRect getOutputRectangle(sf::Vector2i componentPosition) override;
        void press(Array& array);
};


#endif //GAME_SWITCH_HPP
