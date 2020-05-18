#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-static-accessed-through-instance"

#include "Game.hpp"

bool Game::isMouseInsideWindow(sf::Vector2i mousePosition)
{
    sf::Vector2u windowResolution = window.getSize();
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

std::string Game::getDrawText()
{
    sf::Vector2u windowResolution = window.getSize();
    sf::Vector2f pos = player.getPosition();
    sf::Vector2f posMouse = mouseToCellPosition(sf::Mouse::getPosition(window));
    string positionString = "X:" + to_string(pos.x) + " Y:" + to_string(pos.y) + "\nX:" +
                            to_string(posMouse.x) + " Y:" + to_string(posMouse.y) + "\nX:" +
                            to_string((float) player.getPosition().x + windowResolution.x / player.getScale()) + " Y:" +
                            to_string((float) player.getPosition().y + windowResolution.y / player.getScale()) + "\nFPS:" +
                            to_string(fps) + "\n\nTicks per second: " + to_string(ups);
//    string positionString = "Ticks per second: " + to_string(ups);
    return positionString;
}

void Game::jk(sf::Vector2i pos)
{

    sf::Vector2i last;
    bool first = true;
    for (int y = 0; y < 100; y++)
    {
        for (int x = 0; x < 100; x++)
        {
            world.addComponent(Component::Inverter, sf::Vector2i(pos.x + x * 2, pos.y + y * 2), Up, true);
            if (!first)
            {
                world.connect(last, sf::Vector2i(pos.x + x * 2, pos.y + y * 2), false, true);
            }
            first = false;
            last = sf::Vector2i(pos.x + x * 2, pos.y + y * 2);
        }
    }
    world.removeComponent(sf::Vector2i(pos.x + 198, pos.y + 198));
    world.addComponent(Component::Peg, sf::Vector2i(pos.x + 200, pos.y + 197), Rotation::Up, true);
    world.addComponent(Component::Peg, sf::Vector2i(pos.x + 200, pos.y + 199), Up, true);
    world.addComponent(Component::Peg, sf::Vector2i(pos.x - 1, pos.y + 199), Up, true);
    world.addComponent(Component::Peg, sf::Vector2i(pos.x - 1, pos.y), Up, true);

    world.connect(sf::Vector2i(pos.x + 200, pos.y + 197), sf::Vector2i(pos.x + 200, pos.y + 199), true, true);
    world.connect(sf::Vector2i(pos.x + 196, pos.y + 198), sf::Vector2i(pos.x + 200, pos.y + 197), false, true);
    world.connect(sf::Vector2i(pos.x + 200, pos.y + 199), sf::Vector2i(pos.x - 1, pos.y + 199), true, true);
    world.connect(sf::Vector2i(pos.x - 1, pos.y + 199), sf::Vector2i(pos.x - 1, pos.y), true, true);
    world.connect(sf::Vector2i(pos.x - 1, pos.y), sf::Vector2i(pos.x, pos.y), true, true);
}

Game::Game()
{
//    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(120);
    sf::Clock c;
    //jk(sf::Vector2i(0, 0));
    //jk(sf::Vector2i(205, 0));
    //jk(sf::Vector2i(410, 0));
    //jk(sf::Vector2i(615, 0));
    std::cout << c.getElapsedTime().asSeconds() << " seconds" << std::endl;
    
    deltaTimeClock.restart();
    font.loadFromFile("font.ttf");
    //new(&shadowComponent[Component::Nothing]) class BasicComponent;
    new(&shadowComponent[Component::Inverter]) class Inverter;
    new(&shadowComponent[Component::Blotter]) class Blotter;
    new(&shadowComponent[Component::Peg]) class Peg;
    world.logicStart();
}

bool Game::isOpen()
{
    return window.isOpen();
}

bool Game::pollEvent(sf::Event& event)
{
    return window.pollEvent(event);
}

void Game::handleEvent(sf::Event& event)
{
    if (interaction.handleEvent(*this, event))
        return;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (event.type == sf::Event::Closed ||
        (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
    {
        window.close();
        return;
    }
    if (event.type == sf::Event::Resized)
    {
        window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        backgroundBoard.handleResolution(window.getSize(), player.getScale());
    }
    if (window.hasFocus())
    {
        if (isMouseInsideWindow(mousePosition))
        {
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
                backgroundBoard.handleScale(window.getSize(), scale, player.getPosition());
                return;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                bool ret = true;
                if (event.key.code == sf::Keyboard::R)
                    player.rotate();
                else if (event.key.code == sf::Keyboard::Num1)
                    player.setComponent(Component::Nothing);
                else if (event.key.code == sf::Keyboard::Num2)
                    player.setComponent(Component::Peg);
                else if (event.key.code == sf::Keyboard::Num3)
                    player.setComponent(Component::Inverter);
                else if (event.key.code == sf::Keyboard::Num4)
                    player.setComponent(Component::Blotter);
                else
                    ret = false;
                if (ret)
                    return;
            }
        }
    }
}

void Game::update()
{
    interaction.update(*this);
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (window.hasFocus())
    {
        if (isMouseInsideWindow(mousePosition))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                backgroundBoard.handlePlayerPosition(player.handleMousePosition(mousePosition));
                player.startDragging();
            } else
                player.stopDragging();
        } else
            player.stopDragging();
    } else
        player.stopDragging();
    if (world.updateThread.upsClock.getElapsedTime().asMilliseconds() >= 1000)
    {
        ups = world.updateThread.getUps();
        world.updateThread.resetUps(world);
    }
}

void Game::draw()
{
    if (fpsClock.getElapsedTime().asMilliseconds() >= 1000)
    {
        fpsClock.restart();
        fps = fpsCount;
        fpsCount = 0;
    }
    window.clear();
    sf::Clock drawClock;
    backgroundBoard.draw(&window);
    //world.logicPause();
    world.draw(&window, player.getPosition(), player.getScale());
    //world.logicResume();
    interaction.drawShadow(*this);
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
                rectangleShape.setSize(sf::Vector2f(2, 1));
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
                sf::Vector2f posit = ((sf::Vector2f) out->getPosition() + (sf::Vector2f) out->getFragmentPosition() * 16.0f) * 11.0f - player.getPosition();
                rectangleShape.setPosition(posit * (float) player.getScale());
                rectangleShape.setFillColor(sf::Color::Green);
                window.draw(rectangleShape);
            }
        }
        
        sf::RectangleShape rectangleShape;
        rectangleShape.setSize(sf::Vector2f(1, 1));
        rectangleShape.setScale(sf::Vector2f(player.getScale(), player.getScale()));
        rectangleShape.setPosition((worldPosition * 11.0f - player.getPosition()) * (float) player.getScale());
        rectangleShape.setFillColor(sf::Color::White);
        //window.draw(rectangleShape);
        BasicComponent* basicComponent1 = world.getComponent((sf::Vector2i) worldPosition);
        if (basicComponent1 != nullptr);
        //str << "\nBasicComponent:" << basicComponent1 << "\nX:" << worldPosition.x << " Y:" << worldPosition.y << "\nX:" << (int) basicComponent1->getFragmentPosition().x << " Y:" << (int) basicComponent1->getFragmentPosition().y;
    }
    
    if (interaction.isConnecting(*this))
    {
        sf::Vector2f firstPoint = (interaction.getStartConnectionPoint() - player.getPosition()) * (float) player.getScale();
        sf::Vector2f secondPoint = (sf::Vector2f) sf::Mouse::getPosition(window);
        sfLine sfline(firstPoint, secondPoint, sf::Color::Black, player.getScale());
        sfline.draw(window);
    }
    
    //str << "\nDraw time: " << std::setw(6) << std::setfill('0') << drawClock.getElapsedTime().asMicroseconds();

//    sf::Texture shadow = shadowComponent[Component::Inverter].getPreviewTexture();
//    sf::Sprite sprite(shadow);
//    sprite.setColor(sf::Color(255, 255, 255, 100));
//    sprite.setScale(sf::Vector2f(player.getScale(), player.getScale()));
//    window.draw(sprite);
    
    std::string positionString = getDrawText();
    sf::Text text(positionString + str.str(), font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(3); // Position's text thingy
    window.draw(text);
    window.display();
    fpsCount++;
}

#pragma clang diagnostic pop