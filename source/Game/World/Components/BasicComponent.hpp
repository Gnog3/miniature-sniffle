#ifndef GAME_BASICCOMPONENT_HPP
#define GAME_BASICCOMPONENT_HPP


#include <cstdint>
#include <SFML/Graphics.hpp>
#include "Component.hpp"

/*
 * Order:
 *  Wired Inputs
 *  Wired Outputs
 *  Actual Inputs
 *  Actual Outputs
 */
class BasicComponent
{
    protected:
        uint8_t position = 0; // 1 byte
        uint8_t data = 0; // 1 byte (4 bits in use) // 4 bits nothing / currentOut / nextOut / rotation rotation
        uint8_t wiredInAmount = 0; // 1 byte
        uint8_t wiredOutAmount = 0; // 1 byte
        uint16_t actualInAmount = 0; // 2 bytes
        uint16_t actualOutAmount = 0; // 2 bytes
        BasicComponent** pointers = nullptr;


        void addInputWire(BasicComponent* basicComponent);

        void addOutputWire(BasicComponent* basicComponent);

        void addInputActual(BasicComponent* basicComponent);

        void addOutputActual(BasicComponent* basicComponent);

        BasicComponent* getWiredIn(uint8_t index);

        BasicComponent* getWiredOut(uint8_t index);

        BasicComponent* getActualIn(uint16_t index);

        BasicComponent* getActualOut(uint16_t index);

    public:
        BasicComponent() = default;

        BasicComponent(Component component, sf::Vector2u position, uint8_t rotation);

        BasicComponent &operator=(BasicComponent &other);

        ~BasicComponent();

        BasicComponent* connect(BasicComponent* basicComponent);

        uint8_t getPosition() const;

        uint8_t getWiredInAmount() const;

        uint8_t getWiredOutAmount() const;

        uint16_t getActualInAmount() const;

        uint16_t getActualOutAmount() const;

        virtual sf::Sprite getSprite(sf::Texture* texture, sf::Color in, sf::Color out);

        virtual void update();

        virtual void draw(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale);
};


#endif //GAME_BASICCOMPONENT_HPP
