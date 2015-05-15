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
