#include <SFML/Graphics/View.hpp>
#include "Player.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"

void Player::startDragging() {
    dragging = true;
}

void Player::stopDragging() {
    dragging = false;
}

void Player::handleMousePosition(sf::RenderWindow& window, sf::Vector2i mousePosition) {
    if (dragging) {
        sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(mousePosition);
        sf::Vector2f difference = window.mapPixelToCoords(lastMousePosition) - mouseWorldPosition;
        lastMousePosition = mousePosition;
        Game::moveWindow(window, difference);
    } else {
        lastMousePosition = mousePosition;
    }
}

void Player::setComponent(Component component) {
    selectedComponent = component;
}

Component Player::getActiveComponent() {
    return selectedComponent;
}

void Player::setRotation(Rotation rotation) {
    selectedRotation = rotation;
}

Rotation Player::getRotation() {
    return selectedRotation;
}

Rotation Player::rotate(Rotation rotation) {
    switch (rotation) {
        case Rotation::Up:
            return Rotation::Right;
        case Rotation::Right:
            return Rotation::Down;
        case Rotation::Down:
            return Rotation::Left;
        case Rotation::Left:
            return Rotation::Up;
    }
    return Rotation::Up; // Компилятор говорит, что функция может дойти до когца и ничего не вернуть,
    // так что оставлю это здесь. Видимо, баг.
}

void Player::rotate() {
    switch (selectedRotation) {
        case Rotation::Up:
            selectedRotation = Rotation::Right;
            break;
        case Rotation::Right:
            selectedRotation = Rotation::Down;
            break;
        case Rotation::Down:
            selectedRotation = Rotation::Left;
            break;
        case Rotation::Left:
            selectedRotation = Rotation::Up;
            break;
    }
}

PlayerState Player::getState() {
    return state;
}

void Player::setState(PlayerState state) {
    this->state = state;
}

void Player::setZoom(float zoom) {
    this->zoom = zoom;
}

float Player::getZoom() const {
    return zoom;
}


#pragma clang diagnostic pop