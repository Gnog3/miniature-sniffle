#ifndef GAME_FRAGMENT_HPP
#define GAME_FRAGMENT_HPP

#include <SFML/Graphics.hpp>
#include <cstring>
#include "../Components/BasicComponent.hpp"
#include "../Components/Inverter/Inverter.hpp"
#include "../Components/Blotter/Blotter.hpp"
#include "../Components/Component.hpp"


class Fragment
{
    private:
        BasicComponent* componentList;
        uint16_t componentAmount = 0;
        sf::Vector2<uint8_t> position;
    public:

        Fragment(sf::Vector2<uint8_t> position);

        ~Fragment();

        void addComponent(Component component, sf::Vector2u position, uint8_t rotation);

        BasicComponent* getComponent(sf::Vector2<uint8_t> position);

        void draw(sf::RenderWindow* window, sf::Vector2f playerPosition, sf::Vector2f chunkPosition, uint8_t scale);
};


#endif //GAME_FRAGMENT_HPP
