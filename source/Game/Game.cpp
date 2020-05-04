#include <functional>
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
    //window.setFramerateLimit(120);
    windowResolution = window.getSize();
    deltaTimeClock.restart();
    font.loadFromFile("font.ttf");

    const int a = 16;

    for (int i = 13; i < a * 2; i += 2)
    {
        world.addComponent(Component::Inverter, sf::Vector2i(i, i * 2), 1);
    }
    for (int i = 13; i < a * 2 - 2; i += 2)
    {
        world.connect(sf::Vector2i(i, i * 2), sf::Vector2i(i + 2, (i + 2) * 2));
    }






//    world.connect(sf::Vector2i(6, 3), sf::Vector2i(3, 3));

}

bool Game::isOpen()
{
    return window.isOpen();
}

bool Game::pollEvent(sf::Event& event)
{
    return window.pollEvent(event);
}

void Game::handleEvent(sf::Event event)
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
                sf::Vector2f offset = mousePositionAfter - mousePositionBefore;
                player.move(-offset);
                player.setPosition(sf::Vector2f(std::floor(player.getPosition().x * (float) scale) / (float) scale, std::floor(player.getPosition().y * (float) scale) / (float) scale));
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        BasicComponent* basicComponent = world.getComponent(sf::Vector2i(6, 3));
        sf::Vector2i firstPosition = (sf::Vector2i) basicComponent->getPosition();
        BasicComponent* to = basicComponent->getWiredOut(0);
        sf::Vector2i secondPosition = (sf::Vector2i) to->getPosition();
        cout << "X:" << firstPosition.x << " Y:" << firstPosition.y << " -> X:" << secondPosition.x << " Y:" << secondPosition.y << endl;
    }
    float deltaTime = deltaTimeClock.restart().asSeconds();
    fps = 1 / deltaTime;
}

void Game::draw()
{
    // window.clear();
    sf::Vector2f pos = player.getPosition();
    sf::Vector2f posMouse = mouseToCellPosition(sf::Mouse::getPosition(window));
    string positionString = "X:" + to_string(pos.x) + " Y:" + to_string(pos.y) + "\nX:" +
                            to_string(posMouse.x) + " Y:" + to_string(posMouse.y) + "\nX:" +
                            to_string((float) player.getPosition().x + windowResolution.x / player.getScale()) + " Y:" +
                            to_string((float) player.getPosition().y + windowResolution.y / player.getScale()) + "\nFPS:" +
                            to_string(fps);
    backgroundBoard.draw(&window);
    world.draw(&window, player.getPosition(), player.getScale());
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    stringstream str;
    if (isMouseInsideWindow(mousePosition))
    {

        sf::Vector2f mouse = mouseToCellPosition(mousePosition);
        sf::Vector2f worldPosition = (sf::Vector2f) (((sf::Vector2i) mouse) / 11) - sf::Vector2f(mouse.x < 0 ? 1 : 0, mouse.y < 0 ? 1 : 0);
        BasicComponent* basicComponent = world.getComponent((sf::Vector2i) worldPosition);
        if (basicComponent != nullptr)
        {
            for (uint32_t i = 0; i < basicComponent->getActualInAmount(); i++)
            {
                BasicComponent* in = basicComponent->getActualIn(i);
                sf::RectangleShape rectangleShape;
                rectangleShape.setSize(sf::Vector2f(1, 1));
                rectangleShape.setScale(sf::Vector2f(player.getScale(), player.getScale()));
                sf::Vector2f pos = ((sf::Vector2f) in->getPosition() + (sf::Vector2f) in->getFragmentPosition() * 16.0f) * 11.0f - player.getPosition();
                rectangleShape.setPosition(pos * (float) player.getScale());
                rectangleShape.setFillColor(sf::Color::Red);
                window.draw(rectangleShape);
            }
            for (uint32_t i = 0; i < basicComponent->getActualOutAmount(); i++)
            {
                BasicComponent* out = basicComponent->getActualOut(i);
                sf::RectangleShape rectangleShape;
                rectangleShape.setSize(sf::Vector2f(1, 1));
                rectangleShape.setScale(sf::Vector2f(player.getScale(), player.getScale()));
                sf::Vector2f pos = ((sf::Vector2f) out->getPosition() + (sf::Vector2f) out->getFragmentPosition() * 16.0f) * 11.0f - player.getPosition();
                rectangleShape.setPosition(pos * (float) player.getScale());
                rectangleShape.setFillColor(sf::Color::Green);
                window.draw(rectangleShape);
            }
        }

        sf::RectangleShape rectangleShape;
        rectangleShape.setSize(sf::Vector2f(1, 1));
        rectangleShape.setScale(sf::Vector2f(player.getScale(), player.getScale()));
        rectangleShape.setPosition((worldPosition * 11.0f - player.getPosition()) * (float) player.getScale());
        rectangleShape.setFillColor(sf::Color::White);
        window.draw(rectangleShape);
        BasicComponent* basicComponent1 = world.getComponent((sf::Vector2i) worldPosition);
        if (basicComponent1 != nullptr)
            str << "\nBasicComponent:" << basicComponent1 << "\nX:" << worldPosition.x << " Y:" << worldPosition.y << "\nX:" << (int) basicComponent1->getFragmentPosition().x << " Y:" << (int) basicComponent1->getFragmentPosition().y;
    }
    sf::Text text(positionString + str.str(), font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(3); // Position's text thingy
    window.draw(text);
    window.display();
}