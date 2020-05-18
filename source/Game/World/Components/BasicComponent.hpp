#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
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
class Array;
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
#include "../UpdateThread/Array/Array.hpp"

class BasicComponent
{
    protected:
        uint8_t position = 0; // 1 byte
        uint8_t data = 0; // 1 byte (4 bits in use) // 4 bit nothing / in (calculates before update) / outCurrent / outNext / rotation rotation
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
    public:
        bool isWiredOutput(BasicComponent* basicComponent);
        BasicComponent() = default;
        BasicComponent(sf::Vector2<uint8_t> position, sf::Vector2<uint8_t> fragmentPosition, uint8_t componentData);
        void clonePointersArray();
        void scanComponents(std::vector<Connection>& connections);
        sf::Vector2<uint8_t> getFragmentPosition();
        void replacePointer(BasicComponent* from, BasicComponent* to);
        void fixMove(BasicComponent* old, Array& array, bool setup);
        ~BasicComponent();
        void connect(BasicComponent* basicComponent, bool in, Array& array, bool setup);
        void disconnect(BasicComponent* bc, bool in, Array& array, bool setup);
        void disconnectAll(Array& array);
        sf::Vector2<uint8_t> getPosition() const;
        
        inline void calculateInput()
        {
            for (uint16_t i = 0; i < actualInAmount; i++)
                if (getActualIn(i)->getState())
                {
                    data |= 0b10000u;
                    return;
                }
            data &= 0b11101111u;
        }
        
        inline bool getState() const
        { return data & 0b1000u; }
        
        inline bool getInput() const
        { return data & 0b10000u; }
        
        inline void setState(bool state)
        { data = (data & 0b11111011u) | ((uint8_t) ((uint8_t) state << 2u)); }
        
        inline void shiftState(Array& array)
        {
            if (((data & 0b100u) << 1u) != (data & 1000u))
            {
                for (uint16_t i = 0; i < actualOutAmount; i++)
                    array.add(getActualOut(i));
                data = (data & 0b11110111u) | ((data & 0b100u) << 1u);
            }
        }
        
        bool isConnected(BasicComponent* bc, bool in);
        
        inline BasicComponent* getWiredIn(uint8_t index) const
        { return pointers[index]; }
        
        inline BasicComponent* getWiredOut(uint8_t index) const
        { return pointers[wiredInAmount + index]; }
        
        inline BasicComponent* getActualIn(uint16_t index) const
        { return pointers[wiredInAmount + wiredOutAmount + index]; }
        
        inline BasicComponent* getActualOut(uint16_t index) const
        { return pointers[wiredInAmount + wiredOutAmount + actualInAmount + index]; }
        
        inline uint8_t getWiredInAmount() const
        { return wiredInAmount; }
        
        inline uint8_t getWiredOutAmount() const
        { return wiredOutAmount; }
        
        inline uint16_t getActualInAmount() const
        { return actualInAmount; }
        
        inline uint16_t getActualOutAmount() const
        { return actualOutAmount; }
        
        Rotation getRotation() const;
        void setRotation(Rotation rotation);
        void drawPreviewTexture(sf::RenderWindow* window, sf::Vector2f position, uint8_t scale, Rotation rotation);
        virtual Component getComponent();
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

#pragma clang diagnostic pop