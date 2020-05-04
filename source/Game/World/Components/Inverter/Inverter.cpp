
#include "Inverter.hpp" // in out

sf::Sprite Inverter::getBodySprite(sf::Texture* texture)
{
    sf::Sprite sprite;
    texture->create(11, 14);
    uint8_t array[11 * 14 * 4]{
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255,
            0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255,
            0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255,
            0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255,
            0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255,
            0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255,
            0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255,
            0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255,
            0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255,
            0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255,
            0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0, 255
    };
    texture->update(array);
    sprite.setTexture(*texture);
    sprite.setScale(sf::Vector2f(8, 8));
    sprite.setOrigin(sf::Vector2f(5.5, 8.5));
    return sprite;
}

sf::Sprite Inverter::getPegsSprite(sf::Texture* texture, sf::Color in, sf::Color out)
{
    sf::Sprite sprite;
    texture->create(11, 14);
    uint8_t array[11 * 14 * 4]{
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
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
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    texture->update(array);
    sprite.setTexture(*texture);
    sprite.setScale(sf::Vector2f(8, 8));
    sprite.setOrigin(sf::Vector2f(5.5, 8.5));
    return sprite;
}

Inverter::Inverter(sf::Vector2<uint8_t> position, sf::Vector2<uint8_t> fragmentPosition, uint8_t rotation) : BasicComponent(Component::Inverter, position, fragmentPosition, rotation)
{}

sf::Vector2f Inverter::getInputPoint()
{
    // (position & 0b1111u)
    // ((position & 0b11110000u) >> 4u)
    return sf::Vector2((float) (position & 0b1111u) * 11 + 5.5f, (float) ((position & 0b11110000u) >> 4u) * 11 + 5.5f);
}

sf::Vector2f Inverter::getOutputPoint()
{
    uint8_t rotation = data & 0b11u;
    return getInputPoint() + sf::Vector2f(rotation % 2 ? 8.f * (float) (2 - rotation) : 0, rotation % 2 ? 0 : 8.f * (float) (rotation - 1));
}

void Inverter::update()
{
}

void Inverter::drawBody(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale)
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

void Inverter::drawPegs(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale)
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
    state += 1;
    sf::Vector2f position = sf::Vector2f(0b1111u & this->position, (0b11110000u & this->position) >> 4u) * 11.0f;
    sprite[state].setRotation(rotation);
    sprite[state].setScale(sf::Vector2f(scale, scale));
    sprite[state].setPosition(fragmentPosition + (position + sf::Vector2f(5.5f, 5.5f)) * (float) scale);
    window->draw(sprite[state]);
}

