#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;

void celShade(Sprite sprite, RenderWindow* window, Color shadeColor);

Game::Game(RenderWindow* _window)
{
    window = _window;
    loadTextures();
    //myTextureAtlas.setSmooth(true);
}

void Game::update()
{
    //Events
    Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Escape)
            {
                window->close();
            }
        }
        if (event.type == Event::Resized)
        {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            windowWidth = event.size.width;
            windowHeight = event.size.height;
            window->setView(View(visibleArea));
        }
    }

    //Time
    dt = clock.restart();

    //Update objects
    player.update(dt);

    frame++;
}

void Game::draw()
{
    window->clear(Color(255, 255, 255));

    //Set the view
    Vector2f roundedPosition;
    roundedPosition.x = (int)player.getPosition().x;
    roundedPosition.y = (int)player.getPosition().y;

    View view(roundedPosition, Vector2f(windowWidth, windowHeight));
    window->setView(view);


    //Draw the background
    Sprite background;
    background.setTexture(myTextureAtlas);
    Vector2f topLeftTile;// = player.getPosition() - (Vector2f(windowWidth, windowHeight) / 2.0f);

    topLeftTile.x = (int)(player.getPosition().x - windowWidth / 2.0f);
    topLeftTile.x = topLeftTile.x - (int)topLeftTile.x % 16 - 16;

    topLeftTile.y = (int)(player.getPosition().y - windowHeight / 2.0f);
    topLeftTile.y = topLeftTile.y - (int)topLeftTile.y % 16 - 16;

    for (int y = 0; y < (int)(windowHeight / 16.0) + 2; y++)
    {
        for (int x = 0; x < (int)(windowWidth / 16.0) + 2; x++)
        {
            background.setTextureRect(IntRect(randint(0, 7, (y + 1 + topLeftTile.y / 16) * (x + 1 + topLeftTile.x / 16)) * 16, 64, 16, 16));
            background.setPosition(x * 16 + topLeftTile.x, y * 16 + topLeftTile.y);
            window->draw(background);
        }
    }

    //Draw all the objects
    player.draw(window, &myTextureAtlas);
    testPlanet.draw(window, &myTextureAtlas);

    window->display();
}

void Game::loadTextures()
{
    if (!myTextureAtlas.loadFromFile("dontReplaceThis.png"))
        window->close();
    if (!someonesTextureAtlas.loadFromFile("replaceThis.png"))
        window->close();
}

int Game::randint(int low, int high, int seed)
{
    srand(seed);
    int value = rand() % (high + 1 - low) + low;
    return value;
}
