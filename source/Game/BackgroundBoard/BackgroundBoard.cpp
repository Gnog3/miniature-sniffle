#include "BackgroundBoard.hpp"

uint8_t* BackgroundBoard::getColorArray(sf::Color background, sf::Color foreground, uint8_t size, uint8_t thickness)
{
    uint8_t* array = new uint8_t[size * size * 4];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int pointer = (i * size + j) * 4;
            if ((i < thickness) || (i > size - thickness - 1) || (j < thickness) || (j > size - thickness - 1))
            {
                array[pointer + 0] = foreground.r;
                array[pointer + 1] = foreground.g;
                array[pointer + 2] = foreground.b;
                array[pointer + 3] = foreground.a;
            }
            else
            {
                array[pointer + 0] = background.r;
                array[pointer + 1] = background.g;
                array[pointer + 2] = background.b;
                array[pointer + 3] = background.a;
            }
        }
    }
    return array;
}

BackgroundBoard::BackgroundBoard(const sf::Vector2u windowResolution, const uint8_t initScale)
{
    const uint8_t backBrightness = 200;
    const uint8_t foreBrightness = 100;
    const sf::Color background(backBrightness, backBrightness, backBrightness, 255);
    const sf::Color foreground(foreBrightness, foreBrightness, foreBrightness, 255);
    const uint8_t size = 5;
    const uint8_t thickness = 1;
    uint8_t* array = getColorArray(background, foreground, size, thickness);
    texture.create(size, size);
    texture.update(array);
    texture.setRepeated(true);
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(initScale, initScale));
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(windowResolution.x + size * initScale, windowResolution.y + size * initScale)));
    delete array;
}

void BackgroundBoard::handleScale(uint8_t scale, sf::Vector2f playerPosition)
{
    if (scale >= 1 && scale <= 255)
    {
        sprite.setScale(sf::Vector2f(scale, scale));
        handlePlayerPosition(playerPosition);
    }
}

void BackgroundBoard::handlePlayerPosition(sf::Vector2f playerPosition)
{
    const uint8_t size = texture.getSize().x;
    const uint8_t scale = (uint8_t) sprite.getScale().x;
    const uint32_t cellPixelSize = size * scale;
    playerPosition = -playerPosition;
    playerPosition.x = (float) ((int32_t) (playerPosition.x * (float) scale) % (int32_t) cellPixelSize);
    playerPosition.y = (float) ((int32_t) (playerPosition.y * (float) scale) % (int32_t) cellPixelSize);
    playerPosition.x = playerPosition.x < 0 ? cellPixelSize + playerPosition.x : playerPosition.x;
    playerPosition.y = playerPosition.y < 0 ? cellPixelSize + playerPosition.y : playerPosition.y;
    
    //cout << "X:" << offset.x << " Y:" << offset.y << " | X:" << playerPosition.x * scale << " Y:" << playerPosition.y * scale << endl;
    //cout << " | X:" << ((int32_t) (playerPosition.x * (float) scale)) % cellPixelSize << " Y:" << (int32_t) (playerPosition.y * (float) scale) % cellPixelSize << endl;
    sprite.setPosition(playerPosition.x - cellPixelSize, playerPosition.y - cellPixelSize);
    
}

void BackgroundBoard::draw(sf::RenderWindow* window)
{
    window->draw(sprite);
}
