#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-static-accessed-through-instance"

#include "Game.hpp"

bool Game::isMouseInsideWindow(sf::Vector2i mousePosition) {
    sf::Vector2u windowResolution = window.getSize();
    return mousePosition.x >= 0 && mousePosition.y >= 0 && mousePosition.x < windowResolution.x &&
           mousePosition.y < windowResolution.y;
}

std::string Game::getDrawText() {
    sf::View view = window.getView();
    
    sf::Vector2u windowResolution = window.getSize();
    sf::Vector2f pos = window.mapPixelToCoords(sf::Vector2i(0, 0));
    sf::Vector2f posMouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    string positionString = "X:" + to_string(pos.x) + " Y:" + to_string(pos.y) + "\nX:" +
                            to_string(posMouse.x) + " Y:" + to_string(posMouse.y) + "\nFPS: " +
                            to_string(fps) + "\n\nTicks per second: " + to_string(ups);
//    string positionString = "Ticks per second: " + to_string(ups);
    return positionString;
}


void Game::moveWindow(sf::Vector2f offset) {
    Game::moveWindow(window, offset);
}

void Game::moveWindow(sf::RenderWindow& window, sf::Vector2f offset) {
    sf::Vector2u windowSize = window.getSize();
    sf::View view = window.getView();
    view.move(offset);
    window.setView(view);
    sf::Vector2f leftUp = window.mapPixelToCoords(sf::Vector2i(0, 0));
    sf::Vector2f rightDown = window.mapPixelToCoords((sf::Vector2i) windowSize);
    if (leftUp.x < 0)
        view.move(sf::Vector2f(-leftUp.x, 0));
    if (leftUp.y < 0)
        view.move(sf::Vector2f(0, -leftUp.y));
    if (rightDown.x > 65535 * 11)
        view.move(sf::Vector2f(65535 * 11 - rightDown.x, 0));
    if (rightDown.y > 65535 * 11)
        view.move(sf::Vector2f(0, 65535 * 11 - rightDown.y));
    window.setView(view);
}

void Game::jk(sf::Vector2i pos) {
    
    sf::Vector2u last;
    bool first = true;
    uint32_t amount = 0;
    for (uint32_t y = 0; y < 100; y++) {
        for (uint32_t x = 0; x < 100; x++) {
            amount++;
            world.addComponent(Component::Inverter, sf::Vector2u(pos.x + x, pos.y + y * 2), ComponentData::Up, true);
            if (!first) {
                world.connect(last, sf::Vector2u(pos.x + x, pos.y + y * 2), false, true);
            }
            first = false;
            last = sf::Vector2u(pos.x + x, pos.y + y * 2);
        }
    }
    cout << "Amount: " << amount << endl;
//    world.removeComponent(sf::Vector2i(pos.x + 199, pos.y + 198));
//    world.addComponent(Component::Peg, sf::Vector2i(pos.x + 200, pos.y + 197), Rotation::Up, true);
//    world.addComponent(Component::Peg, sf::Vector2i(pos.x + 200, pos.y + 199), Up, true);
//    world.addComponent(Component::Peg, sf::Vector2i(pos.x - 1, pos.y + 199), Up, true);
//    world.addComponent(Component::Peg, sf::Vector2i(pos.x - 1, pos.y), Up, true);
//
//    world.connect(sf::Vector2i(pos.x + 200, pos.y + 197), sf::Vector2i(pos.x + 200, pos.y + 199), true, true);
//    world.connect(sf::Vector2i(pos.x + 196, pos.y + 198), sf::Vector2i(pos.x + 200, pos.y + 197), false, true);
//    world.connect(sf::Vector2i(pos.x + 200, pos.y + 199), sf::Vector2i(pos.x - 1, pos.y + 199), true, true);
//    world.connect(sf::Vector2i(pos.x - 1, pos.y + 199), sf::Vector2i(pos.x - 1, pos.y), true, true);
//    world.connect(sf::Vector2i(pos.x - 1, pos.y), sf::Vector2i(pos.x, pos.y), true, true);
//    `for (int y = 0; y < 200; y++)
//    {
//        for (int x = 0; x < 200; x++)
//        {
//            world.addComponent(Component::Peg, sf::Vector2i(x, y), Up, true);
//        }
//    }`
}

Game::Game() {
//    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(120);
    sf::Clock c;
    //jk(sf::Vector2i(0, 0));
    
    std::cout << c.getElapsedTime().asSeconds() << " seconds" << std::endl;
    
    deltaTimeClock.restart();
    font.loadFromFile("font.ttf");
    //new(&shadowComponent[Component::Nothing]) class BasicComponent;
    new(&shadowComponent[Component::Inverter]) class Inverter;
    new(&shadowComponent[Component::Blotter]) class Blotter;
    new(&shadowComponent[Component::Peg]) class Peg;
    new(&shadowComponent[Component::Switch]) class Switch;
    world.logicStart();
    //moveWindow(sf::Vector2f(32768 * 11, 32768 * 11));
}

bool Game::isOpen() {
    return window.isOpen();
}

bool Game::pollEvent(sf::Event& event) {
    return window.pollEvent(event);
}

void Game::handleEvent(sf::Event& event) {
    if (interaction.handleEvent(*this, event))
        return;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (event.type == sf::Event::Closed ||
        (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
        window.close();
        return;
    }
    if (event.type == sf::Event::Resized) {
        sf::View view = window.getView();
        float zoom = player.getZoom();
        view.setSize((float) event.size.width / zoom, (float) event.size.height / zoom);
        window.setView(view);
        moveWindow(sf::Vector2f(0, 0));
        backgroundBoard.recalculate(window);
    }
    if (window.hasFocus()) {
        if (isMouseInsideWindow(mousePosition)) {
            if (event.type == sf::Event::MouseWheelMoved) {
                int8_t delta = event.mouseWheel.delta;
                float zoom = player.getZoom();
                switch (delta) {
                    case 1:
                        if (zoom < 1.f)
                            zoom *= 2;
                        else
                            zoom++;
                        break;
                    case -1:
                        if (zoom >= (1.f / 16.f)) {
                            if (zoom <= 1.f)
                                zoom /= 2;
                            else
                                zoom--;
                        }
                        break;
                }
                player.setZoom(zoom);
                sf::Vector2u windowSize = window.getSize();
                sf::View view = window.getView();
                view.setSize(windowSize.x / zoom, windowSize.y / zoom);
                window.setView(view);
                moveWindow(sf::Vector2f(0, 0));
                backgroundBoard.recalculate(window);
                return;
            }
            if (event.type == sf::Event::KeyPressed) {
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
                else if (event.key.code == sf::Keyboard::Num5)
                    player.setComponent(Component::Switch);
                else
                    ret = false;
                if (ret)
                    return;
            }
        }
    }
}

void Game::update() {
    interaction.update(*this);
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if (window.hasFocus()) {
        if (isMouseInsideWindow(mousePosition)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                player.handleMousePosition(window, mousePosition);
                backgroundBoard.recalculate(window);
                player.startDragging();
            } else
                player.stopDragging();
        } else
            player.stopDragging();
    } else
        player.stopDragging();
    if (world.updateThread.upsClock.getElapsedTime().asMilliseconds() >= 1000) {
        ups = world.updateThread.getUps();
        world.updateThread.resetUps(world);
    }
    std::this_thread::yield();
}

void Game::draw() {
    if (fpsClock.getElapsedTime().asMilliseconds() >= 1000) {
        fpsClock.restart();
        fps = fpsCount;
        fpsCount = 0;
    }
    window.clear();
    sf::Clock drawClock;
    backgroundBoard.draw(&window);
    //world.logicPause();
    world.draw(window);
    //world.logicResume();
    interaction.drawShadow(*this);
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    
    stringstream str;
    if (isMouseInsideWindow(mousePosition)) {
        
        sf::Vector2f mouse = window.mapPixelToCoords(mousePosition);
        sf::Vector2u worldPosition = (sf::Vector2u) (((sf::Vector2i) mouse) / 11);
        BasicComponent* basicComponent = world.getComponent(worldPosition);
        if (basicComponent != nullptr) {
            for (uint32_t i = 0; i < basicComponent->getActualInAmount(); i++) {
                BasicComponent* in = basicComponent->getActualIn(i);
                sf::RectangleShape rectangleShape;
                rectangleShape.setSize(sf::Vector2f(2, 1));
                sf::Vector2f pos = ((sf::Vector2f) in->getPosition() + (sf::Vector2f) in->getFragmentPosition() * 16.0f) * 11.0f;
                rectangleShape.setPosition(pos);
                rectangleShape.setFillColor(sf::Color::Red);
                window.draw(rectangleShape);
            }
            for (uint32_t i = 0; i < basicComponent->getActualOutAmount(); i++) {
                BasicComponent* out = basicComponent->getActualOut(i);
                sf::RectangleShape rectangleShape;
                rectangleShape.setSize(sf::Vector2f(1, 1));
                sf::Vector2f pos = ((sf::Vector2f) out->getPosition() + (sf::Vector2f) out->getFragmentPosition() * 16.0f) * 11.0f;
                rectangleShape.setPosition(pos);
                rectangleShape.setFillColor(sf::Color::Green);
                window.draw(rectangleShape);
            }
        }
        
        sf::RectangleShape rectangleShape;
        rectangleShape.setSize(sf::Vector2f(1, 1));
        rectangleShape.setPosition((sf::Vector2f) (worldPosition * 11u));
        rectangleShape.setFillColor(sf::Color::White);
        //window.draw(rectangleShape);
        BasicComponent* basicComponent1 = world.getComponent((sf::Vector2u) worldPosition);
        if (basicComponent1 != nullptr);
        //str << "\nBasicComponent:" << basicComponent1 << "\nX:" << worldPosition.x << " Y:" << worldPosition.y << "\nX:" << (int) basicComponent1->getFragmentPosition().x << " Y:" << (int) basicComponent1->getFragmentPosition().y;
    }
    
    if (interaction.isConnecting(*this)) {
        sf::Vector2f firstPoint = interaction.getStartConnectionPoint();
        sf::Vector2f secondPoint = window.mapPixelToCoords(mousePosition);
        sfLine sfline(firstPoint, secondPoint, sf::Color::Black, 1.f);
        sfline.draw(window);
    }
    
    //str << "\nDraw time: " << std::setw(6) << std::setfill('0') << drawClock.getElapsedTime().asMicroseconds();

//    sf::Texture shadow = shadowComponent[Component::Inverter].getPreviewTexture();
//    sf::Sprite sprite(shadow);
//    sprite.setColor(sf::Color(255, 255, 255, 100));
//    sprite.setScale(sf::Vector2f(player.getScale(), player.getScale()));
//    window.draw(sprite);
    sf::View worldView = window.getView();
    sf::Vector2u windowSize = window.getSize();
    sf::View defaultView = sf::View(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
    std::string positionString = getDrawText();
    sf::Text text(positionString + str.str(), font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(3); // Position's text thingy
    window.setView(defaultView);
    window.draw(text);
    window.setView(worldView);
    window.display();
    fpsCount++;
}

#pragma clang diagnostic pop
