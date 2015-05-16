#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;

void celShade(Sprite sprite, RenderWindow* window, Color shadeColor);
int randint(int low, int high, int seed);

Game::Game(RenderWindow* _window)
{
    window = _window;
    loadTextures();
    //myTextureAtlas.setSmooth(true);

    for (int i = 0; i < 50; i++)
    {
        systems.push_back(SolarSystem(Vector2f(randint(-10000, 10000), randint(-10000, 10000))));
    }
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
    totalTime += dt;

    //Update objects
    player.update(dt);
    //testSystem.update(dt);
    for (int i = 0; i < systems.size(); i++)
    {
        systems.at(i).update(dt);
    }

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

    if (Joystick::isButtonPressed(0, 0))
    {
        view.zoom(0.25);
    }
    if (Joystick::isButtonPressed(0, 1))
    {
        view.zoom(0.125);
    }

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
            background.setTextureRect(IntRect(randint(0, 7, (y + 420 + topLeftTile.y / 16) * (x + 420 + topLeftTile.x / 16)) * 16, 64, 16, 16));
            background.setPosition(x * 16 + topLeftTile.x, y * 16 + topLeftTile.y);
            window->draw(background);
        }
    }

    //Draw all the objects
    //testSystem.draw(window, &myTextureAtlas);
    for (int i = 0; i < systems.size(); i++)
    {
        systems.at(i).draw(window, &myTextureAtlas);
    }
    player.draw(window, &myTextureAtlas);
    //testPlanet.draw(window, &myTextureAtlas);

    window->display();
}

void Game::loadTextures()
{
    if (!myTextureAtlas.loadFromFile("dontReplaceThis.png"))
        window->close();
    if (!someonesTextureAtlas.loadFromFile("replaceThis.png"))
        window->close();
}

