#include "BackgroundBoard.hpp"

uint8_t* BackgroundBoard::getColorArray(sf::Color background, sf::Color foreground, uint8_t size, uint8_t thickness) {
    uint8_t* array = new uint8_t[size * size * 4];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int pointer = (i * size + j) * 4;
            if ((i < thickness) || (i > size - thickness - 1) || (j < thickness) || (j > size - thickness - 1)) {
                array[pointer + 0] = foreground.r;
                array[pointer + 1] = foreground.g;
                array[pointer + 2] = foreground.b;
                array[pointer + 3] = foreground.a;
            } else {
                array[pointer + 0] = background.r;
                array[pointer + 1] = background.g;
                array[pointer + 2] = background.b;
                array[pointer + 3] = background.a;
            }
        }
    }
    return array;
}

BackgroundBoard::BackgroundBoard(sf::RenderWindow& window) {
    const uint8_t backBrightness = 170;
    const uint8_t foreBrightness = 110;
    const uint8_t cellSize = 11;
    const uint8_t thickness = 1;
    const sf::Color background(backBrightness, backBrightness, backBrightness, 255);
    const sf::Color foreground(foreBrightness, foreBrightness, foreBrightness, 255);
    uint8_t* array = getColorArray(background, foreground, cellSize, thickness);
    texture.create(cellSize, cellSize);
    texture.update(array);
    texture.setRepeated(true);
    sprite.setTexture(texture);
    sf::View view = window.getView();
    sf::Vector2f boardSize = view.getSize() + sf::Vector2f(cellSize, cellSize);
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(boardSize.x + cellSize, boardSize.y + cellSize)));
    delete[] array;
}

void BackgroundBoard::recalculate(sf::RenderWindow& window) {
    const uint8_t cellSize = texture.getSize().x;
    sf::View view = window.getView();
    sf::Vector2f boardSize = view.getSize() + sf::Vector2f(cellSize, cellSize);
    sf::Vector2i position = (sf::Vector2i) window.mapPixelToCoords(sf::Vector2i(0, 0));
    sprite.setPosition((float) (position.x - (position.x % 11)), (float) (position.y - (position.y % 11)));
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i) boardSize));
}

void BackgroundBoard::draw(sf::RenderWindow* window) {
    window->draw(sprite);
}
