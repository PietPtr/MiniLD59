#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

using namespace sf;
int main()
{
    int windowWidth = 1280;
    int windowHeigth = 720;
    RenderWindow window(VideoMode(windowWidth, windowHeigth), "Float");
    window.setVerticalSyncEnabled(true);

    Game game(&window);

    while (window.isOpen())
    {
        game.update();
        game.draw();
    }

    return 0;
}

void celShade(Sprite sprite, RenderWindow* window, Color shadeColor)
{
    sprite.setColor(shadeColor);
    Vector2f spritePos = sprite.getPosition();
    sprite.setPosition(Vector2f(spritePos.x - 1, spritePos.y));
    window->draw(sprite);
    sprite.setPosition(Vector2f(spritePos.x + 1, spritePos.y));
    window->draw(sprite);
    sprite.setPosition(Vector2f(spritePos.x, spritePos.y - 1));
    window->draw(sprite);
    sprite.setPosition(Vector2f(spritePos.x, spritePos.y + 1));
    window->draw(sprite);
}
