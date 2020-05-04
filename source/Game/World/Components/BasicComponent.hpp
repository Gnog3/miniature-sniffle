#ifndef GAME_BASICCOMPONENT_HPP
#define GAME_BASICCOMPONENT_HPP


#include <cstdint>
#include <vector>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "Component.hpp"
#include "sfLine/sfLine.hpp"

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
        uint16_t actualOutAmount = 0;
        BasicComponent** pointers = nullptr; // 8 bytes
        sf::Vector2<uint8_t> fragmentPosition;

        void insertPointer(BasicComponent* basicComponent, uint32_t offset);

        void addInputWire(BasicComponent* basicComponent);

        void addOutputWire(BasicComponent* basicComponent);

        void addInputActual(BasicComponent* basicComponent);

        void addOutputActual(BasicComponent* basicComponent);

        static bool insertIfNotIn(std::vector<BasicComponent*>& components, BasicComponent* basicComponent);


    public:
        bool isWiredOutput(BasicComponent* basicComponent);

        BasicComponent() = default;

        BasicComponent(Component component, sf::Vector2<uint8_t> position, sf::Vector2<uint8_t> fragmentPosition, uint8_t rotation);

        void clonePointersArray();

        void getRelatedComponents(std::vector<BasicComponent*>& components, bool in, bool out, bool outNeed);

        sf::Vector2<uint8_t> getFragmentPosition();

        void replacePointer(BasicComponent* from, BasicComponent* to);

        void fixMove(BasicComponent& old);

        ~BasicComponent();

        void connect(BasicComponent* basicComponent, bool in);

        sf::Vector2<uint8_t> getPosition() const;

        BasicComponent* getWiredIn(uint8_t index);

        BasicComponent* getWiredOut(uint8_t index);

        BasicComponent* getActualIn(uint16_t index);

        BasicComponent* getActualOut(uint16_t index);

        uint8_t getWiredInAmount() const;

        uint8_t getWiredOutAmount() const;

        uint16_t getActualInAmount() const;

        uint16_t getActualOutAmount() const;

        void setWiredInAmount(uint8_t value);

        void setWiredOutAmount(uint8_t value);

        void setActualInAmount(uint16_t value);

        virtual bool isPeg();

        virtual void drawBody(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale);

        virtual void drawWires(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale);

        virtual void drawPegs(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale);

        virtual sf::Vector2f getInputPoint();

        virtual sf::Vector2f getOutputPoint();

        virtual sf::Sprite getBodySprite(sf::Texture* texture);

        virtual sf::Sprite getPegsSprite(sf::Texture* texture, sf::Color in, sf::Color out);

        virtual void update();


};


#endif //GAME_BASICCOMPONENT_HPP
