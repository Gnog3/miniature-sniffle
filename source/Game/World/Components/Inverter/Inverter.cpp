
#include "Inverter.hpp" // in out

sf::Sprite Inverter::getSprite(sf::Texture* texture, sf::Color in, sf::Color out)
{
    sf::Sprite sprite;
    texture->create(5, 7);
    uint8_t array[]{
            0, 0, 0, 0, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, 0, 0, 0, 0,
            0, 0, 0, 0, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, 0, 0, 0, 0,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, in.r, in.g, in.b, in.a, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
            255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255
    };
    texture->update(array);
    sprite.setTexture(*texture);
    sprite.setScale(sf::Vector2f(8, 8));
    sprite.setOrigin(sf::Vector2f(2.5, 4.5));
    return sprite;
}


Inverter::Inverter(sf::Vector2<uint8_t> position, sf::Vector2<uint8_t> fragmentPosition, uint8_t rotation) : BasicComponent(Component::Inverter, position, fragmentPosition, rotation)
{}

void Inverter::update()
{
}

void Inverter::draw(sf::RenderWindow* window, sf::Vector2f fragmentPosition, uint8_t scale)
{
    static sf::Texture texture[4];
    static sf::Sprite sprite[4]{
            getSprite(&texture[0], sf::Color::Black, sf::Color::Black),
            getSprite(&texture[1], sf::Color::Black, sf::Color::Red),
            getSprite(&texture[2], sf::Color::Red, sf::Color::Black),
            getSprite(&texture[3], sf::Color::Red, sf::Color::Red)
    };
    static sf::Vertex quad[]{
            sf::Vertex(sf::Vector2f(0.0f, 0.0f)),
            sf::Vertex(sf::Vector2f(0.0f, 0.0f)),
            sf::Vertex(sf::Vector2f(0.0f, 0.0f)),
            sf::Vertex(sf::Vector2f(0.0f, 0.0f))
    };
    uint16_t rotation = (0b11 & data) * 90;
    uint8_t state = (0b11000 & data) >> 3;
    state += 1;
    sf::Vector2f position = sf::Vector2f(0b1111 & this->position, (0b11110000 & this->position) >> 4) * 5.0f;
    sprite[state].setRotation(rotation);
    sprite[state].setScale(sf::Vector2f(scale, scale));
    sprite[state].setPosition(fragmentPosition + (position + sf::Vector2f(2.5f, 2.5f)) * (float) scale);
    sf::Vector2f abc = sprite[state].getPosition();
    window->draw(sprite[state]);
    for (uint8_t i = 0; i < wiredOutAmount; i++)
    {
        sf::Vector2<uint8_t> otherPosition = getWiredOut(i)->getPosition();
        std::cout << getWiredOut(i) << std::endl;
    }
}
