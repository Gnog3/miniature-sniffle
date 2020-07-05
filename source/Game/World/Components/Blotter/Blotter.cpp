#include "Blotter.hpp"

sf::Sprite Blotter::getBodySprite(sf::Texture* texture) {
    sf::Sprite sprite;
    texture->create(11, 11);
    uint8_t array[11 * 11 * 4]{
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
    sprite.setOrigin(sf::Vector2f(5.5, 5.5));
    return sprite;
}

sf::Sprite Blotter::getPegsSprite(sf::Texture* texture, sf::Color in, sf::Color out) {
    sf::Sprite sprite;
    texture->create(11, 20);
    uint8_t array[11 * 20 * 4]{
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, out.r, out.g, out.b, out.a, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, in.r, in.g, in.b, in.a, in.r, in.g, in.b, in.a, in.r, in.g, in.b, in.a, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, in.r, in.g, in.b, in.a, in.r, in.g, in.b, in.a, in.r, in.g, in.b, in.a, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, in.r, in.g, in.b, in.a, in.r, in.g, in.b, in.a, in.r, in.g, in.b, in.a, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, in.r, in.g, in.b, in.a, in.r, in.g, in.b, in.a, in.r, in.g, in.b, in.a, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, in.r, in.g, in.b, in.a, in.r, in.g, in.b, in.a, in.r, in.g, in.b, in.a, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, in.r, in.g, in.b, in.a, in.r, in.g, in.b, in.a, in.r, in.g, in.b, in.a, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    texture->update(array);
    sprite.setTexture(*texture);
    sprite.setOrigin(sf::Vector2f(5.5, 8.5));
    return sprite;
}

Blotter::Blotter() : BasicComponent() {}

Blotter::Blotter(sf::Vector2<uint8_t> position, sf::Vector2<uint8_t> fragmentPosition, uint8_t rotation) : BasicComponent(position, fragmentPosition, rotation) {}

Component Blotter::getComponent() {
    return Component::Blotter;
}

sf::Vector2f Blotter::getInputPoint() {
    uint8_t rotation = data & 0b11u;
    return sf::Vector2f((rotation % 2 ? -11.f * (float) (2 - rotation) : 0) + (float) (position & 0b1111u) * 11.f + 5.5f,
                        (rotation % 2 ? 0 : -11.f * (float) (rotation - 1)) + (float) ((position & 0b11110000u) >> 4u) * 11.f + 5.5f);
}

sf::Vector2f Blotter::getOutputPoint() {
    uint8_t rotation = data & 0b11u;
    return sf::Vector2f((rotation % 2 ? 8.f * (float) (2 - rotation) : 0) + (float) (position & 0b1111u) * 11.f + 5.5f,
                        (rotation % 2 ? 0 : 8.f * (float) (rotation - 1)) + (float) ((position & 0b11110000u) >> 4u) * 11.f + 5.5f);
}

sf::IntRect Blotter::getBodyRectangle(sf::Vector2u componentPosition) {
    return sf::IntRect(componentPosition.x, componentPosition.y, 11, 11);
}

sf::IntRect Blotter::getInputRectangle(sf::Vector2u componentPosition) {
    Rotation rotation = Rotation(data & 0b11u);
    switch (rotation) {
        case Rotation::Up:
            return sf::IntRect(componentPosition.x + 4, componentPosition.y + 11, 3, 6);
        case Rotation::Right:
            return sf::IntRect(componentPosition.x - 6, componentPosition.y + 4, 6, 3);
        case Rotation::Down:
            return sf::IntRect(componentPosition.x + 4, componentPosition.y - 6, 3, 6);
        case Rotation::Left:
            return sf::IntRect(componentPosition.x + 11, componentPosition.y + 4, 6, 3);
    }
    std::cout << "error не знаю почему но компилятор ругается" << std::endl;
    std::exit(-123);
}

sf::IntRect Blotter::getOutputRectangle(sf::Vector2u componentPosition) {
    Rotation rotation = Rotation(data & 0b11u);
    switch (rotation) {
        case Rotation::Up:
            return sf::IntRect(componentPosition.x + 3, componentPosition.y - 3, 5, 3);
        case Rotation::Right:
            return sf::IntRect(componentPosition.x + 11, componentPosition.y + 3, 3, 5);
        case Rotation::Down:
            return sf::IntRect(componentPosition.x + 3, componentPosition.y + 11, 5, 3);
        case Rotation::Left:
            return sf::IntRect(componentPosition.x - 3, componentPosition.y + 3, 3, 5);
    }
    std::cout << "error не знаю почему но компилятор ругается" << std::endl;
    std::exit(-123);
}

void Blotter::update() {
    setState(getInput());
}

