#ifndef GAME_BASICCOMPONENT_HPP
#define GAME_BASICCOMPONENT_HPP


#include <cstdint>
#include <vector>
#include <cstring>
#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include "../../Rotation.hpp"
#include "Component.hpp"
#include "sfLine/sfLine.hpp"

/*
 * Order:
 *  Wired Inputs
 *  Wired Outputs
 *  Actual Inputs
 *  Actual Outputs
 */
class BasicComponent;

struct Connection
{
    BasicComponent* component;
    bool isOutput;
};

enum Scan : bool
{
    Input = false,
    Output = true
};

class BasicComponent
{
    protected:
        uint8_t position = 0; // 1 byte
        uint8_t data = 0; // 1 byte (4 bits in use) // 4 bits nothing / currentOut / nextOut / rotation rotation
        uint8_t wiredInAmount = 0; // 1 byte
        uint8_t wiredOutAmount = 0; // 1 byte
        uint16_t actualInAmount = 0; // 2 bytes
        uint16_t actualOutAmount = 0; // 2 bytes
        BasicComponent** pointers = nullptr; // 8 bytes
        sf::Vector2<uint8_t> fragmentPosition; // 2 bytes
        
        void insertPointer(BasicComponent* basicComponent, uint32_t offset);
        void removePointer(uint32_t index);
        void addInputWire(BasicComponent* basicComponent);
        void addOutputWire(BasicComponent* basicComponent);
        void addInputActual(BasicComponent* basicComponent);
        void addOutputActual(BasicComponent* basicComponent);
        void removeInputWire(BasicComponent* basicComponent);
        void removeOutputWire(BasicComponent* basicComponent);
        void removeInputActual(BasicComponent* basicComponent);
        void removeOutputActual(BasicComponent* basicComponent);
        static bool insertIfNotIn(std::vector<Connection>& connections, Connection connection);
        void clearActualIn();
        void clearActualOut();
    public:
        bool isWiredOutput(BasicComponent* basicComponent);
        BasicComponent() = default;
        BasicComponent(Component component, sf::Vector2<uint8_t> position, sf::Vector2<uint8_t> fragmentPosition, uint8_t rotation);
        void clonePointersArray();
        void scanComponents(std::vector<Connection>& connections, Scan scan, bool first);
        sf::Vector2<uint8_t> getFragmentPosition();
        void replacePointer(BasicComponent* from, BasicComponent* to);
        void fixMove(BasicComponent& old);
        ~BasicComponent();
        void recalculateActuals();
        void connect(BasicComponent* basicComponent, bool in);
        void disconnect(BasicComponent* bc, bool in);
        sf::Vector2<uint8_t> getPosition() const;
        bool getOutputState();
        bool isConnected(BasicComponent* bc, bool in);
        BasicComponent* getWiredIn(uint8_t index);
        BasicComponent* getWiredOut(uint8_t index);
        BasicComponent* getActualIn(uint16_t index);
        BasicComponent* getActualOut(uint16_t index);
        uint8_t getWiredInAmount() const;
        uint8_t getWiredOutAmount() const;
        uint16_t getActualInAmount() const;
        uint16_t getActualOutAmount() const;
        Rotation getRotation() const;
        void setRotation(Rotation rotation);
        void setWiredInAmount(uint8_t value);
        void setWiredOutAmount(uint8_t value);
        void setActualInAmount(uint16_t value);
        void drawPreviewTexture(sf::RenderWindow* window, sf::Vector2f position, uint8_t scale, Rotation rotation);
        virtual bool isPeg();
        virtual void drawBody(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale);
        virtual void drawWires(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale);
        virtual void drawPegs(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale);
        virtual sf::Vector2f getInputPoint();
        virtual sf::Vector2f getOutputPoint();
        virtual sf::IntRect getBodyRectangle(sf::Vector2i componentPosition);
        virtual sf::IntRect getInputRectangle(sf::Vector2i componentPosition);
        virtual sf::IntRect getOutputRectangle(sf::Vector2i componentPosition);
        virtual sf::Sprite getBodySprite(sf::Texture* texture);
        virtual sf::Sprite getPegsSprite(sf::Texture* texture, sf::Color in, sf::Color out);
        virtual void update();
};


#endif //GAME_BASICCOMPONENT_HPP
