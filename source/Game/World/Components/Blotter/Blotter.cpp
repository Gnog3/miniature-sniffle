#include "Blotter.hpp"

Blotter::Blotter() : BasicComponent()
{}

Blotter::Blotter(sf::Vector2<uint8_t> position, sf::Vector2<uint8_t> fragmentPosition, uint8_t rotation) : BasicComponent(Component::Inverter, position, fragmentPosition, rotation)
{}