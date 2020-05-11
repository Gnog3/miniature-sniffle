#include "Peg.hpp"

sf::Sprite Peg::getBodySprite(sf::Texture* texture)
{
    sf::Sprite sprite;
    texture->create(11, 11);
    uint8_t array[11 * 11 * 4]{
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    texture->update(array);
    sprite.setTexture(*texture);
    sprite.setScale(sf::Vector2f(8, 8));
    sprite.setOrigin(sf::Vector2f(5.5, 5.5));
    return sprite;
}

sf::Sprite Peg::getPegsSprite(sf::Texture* texture, sf::Color in, sf::Color out)
{
    sf::Sprite sprite;
    texture->create(11, 11);
    uint8_t array[11 * 11 * 4]{
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, in.r, in.g, in.b, in.a, in.r, in.g, in.b, in.a, in.r, in.g, in.b, in.a, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, in.r, in.g, in.b, in.a, in.r, in.g, in.b, in.a, in.r, in.g, in.b, in.a, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, in.r, in.g, in.b, in.a, in.r, in.g, in.b, in.a, in.r, in.g, in.b, in.a, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    texture->update(array);
    sprite.setTexture(*texture);
    sprite.setScale(sf::Vector2f(8, 8));
    sprite.setOrigin(sf::Vector2f(5.5, 5.5));
    return sprite;
}

Peg::Peg() : BasicComponent()
{}

Peg::Peg(sf::Vector2<uint8_t> position, sf::Vector2<uint8_t> fragmentPosition) : BasicComponent(Component::Inverter, position, fragmentPosition, 0)
{}

bool Peg::isPeg()
{
    return true;
}

sf::Vector2f Peg::getInputPoint()
{
    return sf::Vector2((float) (position & 0b1111u) * 11 + 5.5f, (float) ((position & 0b11110000u) >> 4u) * 11 + 5.5f);
}

sf::Vector2f Peg::getOutputPoint()
{
    uint8_t rotation = data & 0b11u;
    return getInputPoint() + sf::Vector2f(rotation % 2 ? 8.f * (float) (2 - rotation) : 0, rotation % 2 ? 0 : 8.f * (float) (rotation - 1));
}

sf::IntRect Peg::getBodyRectangle(sf::Vector2i componentPosition)
{
    return sf::IntRect(componentPosition.x + 2, componentPosition.y + 2, 9, 9);
}

sf::IntRect Peg::getInputRectangle(sf::Vector2i componentPosition)
{
    return sf::IntRect(componentPosition.x + 4, componentPosition.y + 4, 3, 3);
}

sf::IntRect Peg::getOutputRectangle(sf::Vector2i componentPosition)
{
    return sf::IntRect();
}

void Peg::drawBody(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale)
{
    static sf::Texture texture;
    static sf::Sprite sprite = getBodySprite(&texture);
    uint16_t rotation = (0b11u & data) * 90;
    sf::Vector2f position = sf::Vector2f(0b1111u & this->position, (0b11110000u & this->position) >> 4u) * 11.0f;
    sprite.setRotation(rotation);
    sprite.setScale(sf::Vector2f(scale, scale));
    sprite.setPosition(fragmentPosition + (position + sf::Vector2f(5.5f, 5.5f)) * (float) scale);
    window->draw(sprite);
}

void Peg::drawWires(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale)
{
    for (uint8_t i = 0; i < wiredInAmount; i++)
    {
        sf::Vector2i fragmentDifference = (sf::Vector2i) (getWiredIn(i)->getFragmentPosition() - this->fragmentPosition);
        fragmentDifference.x = fragmentDifference.x > 128 ? fragmentDifference.x - 256 : fragmentDifference.x;
        fragmentDifference.x = fragmentDifference.x <= -128 ? fragmentDifference.x + 256 : fragmentDifference.x;
        fragmentDifference.y = fragmentDifference.y > 128 ? fragmentDifference.y - 256 : fragmentDifference.y;
        fragmentDifference.y = fragmentDifference.y <= -128 ? fragmentDifference.y + 256 : fragmentDifference.y;
        sf::Vector2f first = (getWiredIn(i)->isWiredOutput(this) ? getWiredIn(i)->getOutputPoint() : getWiredIn(i)->getInputPoint()) * (float) scale + fragmentPosition;
        first += (sf::Vector2f) (fragmentDifference * 16 * 11 * (int) scale);
        sf::Vector2f second = getInputPoint() * (float) scale + fragmentPosition;
        sfLine sfline(first, second, getInput() ? sf::Color::Red : sf::Color::Black, scale);
        sfline.draw(*window);
    }
}

void Peg::drawPegs(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale)
{
    static sf::Texture texture[4];
    static sf::Sprite sprite[4]{
            getPegsSprite(&texture[0], sf::Color(0, 0, 0, 255), sf::Color(0, 0, 0, 255)),
            getPegsSprite(&texture[1], sf::Color(0, 0, 0, 255), sf::Color::Red),
            getPegsSprite(&texture[2], sf::Color::Red, sf::Color(0, 0, 0, 255)),
            getPegsSprite(&texture[3], sf::Color::Red, sf::Color::Red)
    };
    uint16_t rotation = (0b11u & data) * 90;
    uint8_t state = (0b11000u & data) >> 3u;
    state += 0;
    sf::Vector2f position = sf::Vector2f(0b1111u & this->position, (0b11110000u & this->position) >> 4u) * 11.0f;
    sprite[state].setRotation(rotation);
    sprite[state].setScale(sf::Vector2f(scale, scale));
    sprite[state].setPosition(fragmentPosition + (position + sf::Vector2f(5.5f, 5.5f)) * (float) scale);
    window->draw(sprite[state]);
}
