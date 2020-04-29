#include "Player.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"

void Player::move(sf::Vector2f offset)
{
    position += offset;
}

void Player::startDragging()
{
    dragging = true;
}

void Player::stopDragging()
{
    dragging = false;
}

void Player::setScale(uint8_t scale)
{
    this->scale = scale >= 1 && scale <= 255 ? scale : 1;
}

uint8_t Player::getScale() const
{
    return scale;
}

sf::Vector2f Player::handleMousePosition(sf::Vector2i mousePosition)
{
    if (dragging)
    {
        const float sensitivity = 0.5f;
        sf::Vector2i difference = mousePosition - lastMousePosition;
        lastMousePosition = mousePosition;
        sf::Vector2f newPosition = position + sf::Vector2f(- difference.x, - difference.y) / (float) scale;
        position = sf::Vector2f((newPosition.x * 1) / 1, (newPosition.y * 1) / 1);
    }
    else
    {
        lastMousePosition = mousePosition;
    }
    return position;
}

sf::Vector2f Player::getPosition()
{
    return position;
}

#pragma clang diagnostic pop