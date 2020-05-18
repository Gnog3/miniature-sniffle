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
        sf::Vector2f newPosition = position + sf::Vector2f(-difference.x, -difference.y) / (float) scale;
        position = sf::Vector2f((newPosition.x * 1) / 1, (newPosition.y * 1) / 1);
    } else
    {
        lastMousePosition = mousePosition;
    }
    return getPosition();
}

void Player::setPosition(sf::Vector2f value)
{
    position = value;
}

sf::Vector2f Player::getPosition() const
{
    if (scale == 1)
        return sf::Vector2f((int) position.x, (int) position.y);
    else
        return sf::Vector2f(std::floor(position.x * (float) scale) / (float) scale, std::floor(position.y * (float) scale) / (float) scale);
}

void Player::setComponent(Component component)
{
    selectedComponent = component;
}

Component Player::getActiveComponent()
{
    return selectedComponent;
}

void Player::setRotation(Rotation rotation)
{
    selectedRotation = rotation;
}

Rotation Player::getRotation()
{
    return selectedRotation;
}

Rotation Player::rotate(Rotation rotation)
{
    switch (rotation)
    {
        case Up:
            return Right;
        case Right:
            return Down;
        case Down:
            return Left;
        case Left:
            return Up;
    }
    return Up; // Компилятор говорит, что функция может дойти до когца и ничего не вернуть,
    // так что оставлю это здесь. Видимо, баг.
}

void Player::rotate()
{
    switch (selectedRotation)
    {
        case Up:
            selectedRotation = Right;
            break;
        case Right:
            selectedRotation = Down;
            break;
        case Down:
            selectedRotation = Left;
            break;
        case Left:
            selectedRotation = Up;
            break;
    }
}

PlayerState Player::getState()
{
    return state;
}

void Player::setState(PlayerState state)
{
    this->state = state;
}


#pragma clang diagnostic pop