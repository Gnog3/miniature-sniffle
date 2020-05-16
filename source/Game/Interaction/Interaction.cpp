#include "Interaction.hpp"

bool Interaction::handleConnectionTry(Game& game)
{
    if (game.player.getActiveComponent() != Nothing)
        return false;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(game.window);
    sf::Vector2f mouseCellPosition = game.mouseToCellPosition(mousePosition);
    sf::Vector2i cell(std::floor(mouseCellPosition.x / 11.f),
                      std::floor(mouseCellPosition.y / 11.f));
    bool reset = false;
    for (int32_t y = cell.y - 1; y <= cell.y + 1; y++)
    {
        for (int32_t x = cell.x - 1; x <= cell.x + 1; x++)
        {
            BasicComponent* basicComponent = game.world.getComponent(sf::Vector2i(x, y));
            if (basicComponent == nullptr)
                continue;
            sf::IntRect inputRect = basicComponent->getInputRectangle(sf::Vector2i(x, y) * 11 +
                                                                      sf::Vector2i(x < 0 ? 1 : 0, y < 0 ? 1 : 0)); // Костыль. Не знаю почему, но при минусовой координате оно смещается, так что нужно сместить обратно
            sf::IntRect outputRect = basicComponent->getOutputRectangle(sf::Vector2i(x, y) * 11 +
                                                                        sf::Vector2i(x < 0 ? 1 : 0, y < 0 ? 1 : 0)); // ^^
            if (game.player.getState() == Normal)
            {
                if (inputRect.contains((sf::Vector2i) mouseCellPosition))
                {
                    game.player.setState(WireDrawFromInput);
                    connectionComponent = basicComponent;
                    connectionPosition = sf::Vector2i(x, y);
                    connectionPositionDraw = (sf::Vector2f) (sf::Vector2i(x, y) - sf::Vector2i(x < 0 ? (16 + (x % 16)) % 16 : x % 16,
                                                                                               y < 0 ? (16 + (y % 16)) % 16 : y % 16)) * 11.f + basicComponent->getInputPoint();
                    return true;
                } else if (outputRect.contains((sf::Vector2i) mouseCellPosition))
                {
                    game.player.setState(WireDrawFromOutput);
                    connectionComponent = basicComponent;
                    connectionPosition = sf::Vector2i(x, y);
                    connectionPositionDraw = (sf::Vector2f) (sf::Vector2i(x, y) - sf::Vector2i(x < 0 ? (16 + (x % 16)) % 16 : x % 16, y < 0 ? (16 + (y % 16)) % 16 : y % 16)) * 11.f + basicComponent->getOutputPoint();
                    return true;
                }
            } else if (game.player.getState() == WireDrawFromOutput)
            {
                if (inputRect.contains((sf::Vector2i) mouseCellPosition) && basicComponent != connectionComponent)
                {
                    if (!game.world.isConnected(connectionPosition, sf::Vector2i(x, y)))
                    {
                        game.world.logicPause();
                        game.world.connect(connectionPosition, sf::Vector2i(x, y), false, false);
                        game.world.logicResume();
                    } else
                    {
                        game.world.logicPause();
                        game.world.disconnect(connectionPosition, sf::Vector2i(x, y), false, false);
                        game.world.logicResume();
                    }
                }
            } else if (game.player.getState() == WireDrawFromInput)
            {
                if (inputRect.contains((sf::Vector2i) mouseCellPosition) && basicComponent != connectionComponent)
                {
                    if (!game.world.isConnected(connectionPosition, sf::Vector2i(x, y), true))
                    {
                        game.world.logicPause();
                        game.world.connect(connectionPosition, sf::Vector2i(x, y), true, false);
                        game.world.logicResume();
                    } else
                    {
                        game.world.logicPause();
                        game.world.disconnect(connectionPosition, sf::Vector2i(x, y), true, false);
                        game.world.logicResume();
                    }
                } else if (outputRect.contains((sf::Vector2i) mouseCellPosition) && basicComponent != connectionComponent)
                {
                    if (!game.world.isConnected(sf::Vector2i(x, y), connectionPosition))
                    {
                        game.world.logicPause();
                        game.world.connect(sf::Vector2i(x, y), connectionPosition, false, false);
                        game.world.logicResume();
                    } else
                    {
                        game.world.logicPause();
                        game.world.disconnect(sf::Vector2i(x, y), connectionPosition, false, false);
                        game.world.logicResume();
                    }
                }
            }
        }
    }
    if (game.player.getState() == WireDrawFromInput || game.player.getState() == WireDrawFromOutput)
    {
        game.player.setState(Normal);
        connectionComponent = nullptr;
        connectionPosition = sf::Vector2i();
        connectionPositionDraw = sf::Vector2f();
        return true;
    }
    return false;
}

bool Interaction::handleNewComponentTry(Game& game)
{
    if (game.player.getActiveComponent() == Nothing)
        return false;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(game.window);
    sf::Vector2f mouseCellPosition = game.mouseToCellPosition(mousePosition);
    sf::Vector2i cell(std::floor(mouseCellPosition.x / 11), std::floor(mouseCellPosition.y / 11));
    BasicComponent* component = game.world.getComponent(cell);
    if (component != nullptr)
        return false;
    bool intersects = false;
    {
        game.shadowComponent[game.player.getActiveComponent()].setRotation(game.player.getRotation());
        std::vector<sf::IntRect> newCompRects{
                game.shadowComponent[game.player.getActiveComponent()].getBodyRectangle(cell * 11),
                game.shadowComponent[game.player.getActiveComponent()].getInputRectangle(cell * 11),
                game.shadowComponent[game.player.getActiveComponent()].getOutputRectangle(cell * 11)
        };
        for (int32_t y = cell.y - 1; y <= cell.y + 1; y++)
        {
            for (int32_t x = cell.x - 1; x <= cell.x + 1; x++)
            {
                BasicComponent* basicComponent = game.world.getComponent(sf::Vector2i(x, y));
                if (basicComponent == nullptr)
                    continue;
                std::vector<sf::IntRect> compRects{
                        basicComponent->getBodyRectangle(sf::Vector2i(x, y) * 11),
                        basicComponent->getInputRectangle(sf::Vector2i(x, y) * 11),
                        basicComponent->getOutputRectangle(sf::Vector2i(x, y) * 11)
                };
                for (auto& newCompRect : newCompRects)
                    for (auto& compRect : compRects)
                        if (newCompRect.intersects(compRect))
                        {
                            intersects = true;
                        }
            }
        }
    }
    if (!intersects)
    {
        game.world.logicPause();
        game.world.addComponent(game.player.getActiveComponent(), cell, game.player.getRotation(), false);
        game.world.logicResume();
    }
    return true;
}

bool Interaction::handleRemoveComponentTry(Game& game)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(game.window);
    sf::Vector2f mouseCellPosition = game.mouseToCellPosition(mousePosition);
    sf::Vector2i cell(std::floor(mouseCellPosition.x / 11), std::floor(mouseCellPosition.y / 11));
    BasicComponent* component = game.world.getComponent(cell);
    if (component == nullptr)
        return false;
    game.world.logicPause();
    game.world.updateThread.array->deleteComponent(component);
    game.world.removeComponent(cell);
    game.world.logicResume();
    return true;
}

bool Interaction::isConnecting(Game& game)
{
    return game.player.getState() == WireDrawFromOutput ||
           game.player.getState() == WireDrawFromInput;
}

sf::Vector2f Interaction::getStartConnectionPoint()
{
    return connectionPositionDraw;
}

void Interaction::drawShadow(Game& game)
{
    Component component = game.player.getActiveComponent();
    if (component == Nothing)
        return;
    sf::Vector2f mousePosition = game.mouseToCellPosition(sf::Mouse::getPosition(game.window));
    sf::Vector2f cellPosition(std::floor(mousePosition.x / 11),
                              std::floor(mousePosition.y / 11));
    if (game.world.getComponent((sf::Vector2i) cellPosition) != nullptr)
        return;
    sf::Vector2f playerPosition = game.player.getPosition();
    sf::Vector2f position((cellPosition.x * 11 - playerPosition.x) * (float) game.player.getScale(),
                          (cellPosition.y * 11 - playerPosition.y) * (float) game.player.getScale());
    
    game.shadowComponent[component].drawPreviewTexture(&game.window, position, game.player.getScale(), game.player.getRotation());
}

bool Interaction::handleEvent(Game& game, sf::Event& event)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(game.window);
    if (game.window.hasFocus())
    {
        if (game.isMouseInsideWindow(mousePosition))
        {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (handleConnectionTry(game))
                    return true;
                if (handleNewComponentTry(game))
                    return true;
            }
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T)
        {
            if (handleRemoveComponentTry(game))
                return true;
        }
    }
    return false;
}

bool Interaction::update(Game& game)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(game.window);
    if (game.window.hasFocus())
    {
        if (game.isMouseInsideWindow(mousePosition))
        {
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (handleNewComponentTry(game))
                return true;
        }
    }
    return false;
}
