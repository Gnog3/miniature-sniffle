#include "Game.hpp"

bool Game::isMouseInsideWindow(sf::Vector2i mousePosition)
{
    return mousePosition.x >= 0 && mousePosition.y >= 0 && mousePosition.x < windowResolution.x &&
           mousePosition.y < windowResolution.y;
}

sf::Vector2f Game::mouseToCellPosition(sf::Vector2i mousePosition)
{
    uint8_t scale = player.getScale();
    sf::Vector2f position = player.getPosition();
    return sf::Vector2f(
            position + sf::Vector2f((float) mousePosition.x / (float) scale, (float) mousePosition.y / (float) scale));
}

Game::Game()
{
    //window.setVerticalSyncEnabled(true);
    windowResolution = window.getSize();
    deltaTimeClock.restart();
    font.loadFromFile("Arial.ttf");
    //world.addComponent(Component::Inverter, sf::Vector2i(0, 0), 0);
    world.addComponent(Component::Inverter, sf::Vector2i(3, 3), 0);
    world.addComponent(Component::Inverter, sf::Vector2i(5, 3), 3);
    world.addComponent(Component::Inverter, sf::Vector2i(7, 3), 2);
    world.addComponent(Component::Inverter, sf::Vector2i(9, 3), 1);
    world.addComponent(Component::Inverter, sf::Vector2i(20, 3), 0);
    world.addComponent(Component::Inverter, sf::Vector2i(-1, -1), 0);
    world.addComponent(Component::Inverter, sf::Vector2i(-1, -1), 1);
}

bool Game::isOpen()
{
    return window.isOpen();
}

bool Game::pollEvent(sf::Event &event)
{
    return window.pollEvent(event);
}

void Game::handleUpdate(sf::Event event)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (event.type == sf::Event::Closed ||
        (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
    {
        window.close();
    }
    if (window.hasFocus())
    {
        if (isMouseInsideWindow(mousePosition))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                backgroundBoard.handlePlayerPosition(player.handleMousePosition(mousePosition));
                player.startDragging();
            } else
            {
                player.stopDragging();
            }
            if (event.type == sf::Event::MouseWheelMoved)
            {
                int8_t delta = event.mouseWheel.delta;
                uint8_t scale = player.getScale();
                sf::Vector2f mousePositionBefore = mouseToCellPosition(mousePosition);
                switch (delta)
                {
                    case 1:
                        scale = scale < 255 ? scale + 1 : scale;
                        break;
                    case (-1):
                        scale = scale > 1 ? scale - 1 : scale;
                        break;
                }
                player.setScale(scale);
                sf::Vector2f mousePositionAfter = mouseToCellPosition(mousePosition);
                sf::Vector2f offset = (sf::Vector2f)(sf::Vector2i)(mousePositionAfter - mousePositionBefore);
                player.move(-offset);
                backgroundBoard.handleScale(scale, player.getPosition());

            }
        } else
        {
            player.stopDragging();
        }
    }
}

void Game::update()
{
    float deltaTime = deltaTimeClock.restart().asSeconds();
    fps = 1 / deltaTime;
}

void Game::draw()
{
    window.clear();
    sf::Vector2f pos = player.getPosition();
    sf::Vector2f posMouse = mouseToCellPosition(sf::Mouse::getPosition(window));
    string positionString = "X:" + to_string(pos.x) + " Y:" + to_string(pos.y) + "\nX:" +
                            to_string(posMouse.x) + " Y:" + to_string(posMouse.y) + "\nX:" +
                            to_string((float) player.getPosition().x + windowResolution.x / player.getScale()) + " Y:" +
                            to_string((float) player.getPosition().y + windowResolution.y / player.getScale()) + "\nFPS:" +
                            to_string(fps);
    sf::Text text(positionString, font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(3); // Position's text thingy
    backgroundBoard.draw(&window);
    world.draw(&window, player.getPosition(), player.getScale());
    window.draw(text);
    window.display();
}