#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include "Game.h"

#define GREEN Color(0, 200, 0)
#define WHITE Color(255, 255, 255)

using namespace sf;

void celShade(Sprite sprite, RenderWindow* window, Color shadeColor);
int randint(int low, int high, int seed);
void drawString(RenderWindow* window, std::string text, Vector2f position, Texture* fontTexture, Color color, int newLine);

Game::Game(RenderWindow* _window)
{
    window = _window;
    loadTextures();
    loadMusic();

    loadTextFile("text/names.txt", &baseNames);
    loadTextFile("text/rockPlanets.txt", &rockPlanetSentences);
    loadTextFile("text/gasPlanets.txt", &gasPlanetSentences);
    loadTextFile("text/traits.txt", &traits);
    loadTextFile("text/adj.txt", &adjectives);
    loadTextFile("text/people.txt", &people);
    loadTextFile("text/nouns.txt", &nouns);

    data.names = &baseNames;
    data.rockPlanetSentences = &rockPlanetSentences;
    data.gasPlanetSentences = &gasPlanetSentences;
    data.traits = &traits;
    data.adjectives = &adjectives;
    data.nouns = &nouns;
    data.people = &people;
    //myTextureAtlas.setSmooth(true);
}

void Game::initialize()
{
    backgroundMusic.play();
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
            else if (event.key.code == Keyboard::Return && gameState == PLAY)
            {
                if (radar)
                {
                    radar = false;
                    radarRadius = 0;
                }
                else
                {
                    radar = true;
                }
            }
            else if (event.key.code == Keyboard::F2)
            {
                if (useTexture == &myTextureAtlas)
                    useTexture = &someonesTextureAtlas;
                else if (useTexture == &someonesTextureAtlas)
                    useTexture = &myTextureAtlas;
            }
            else if (event.key.code == Keyboard::Space && gameState == PLAY && getDistance(entryPopupPos, player.getPosition()) < 15)
            {
                gameState = READ;
                gameStateTime = totalTime;
            }
            else if (event.key.code == Keyboard::Space && gameState == READ)
            {
                gameState = PLAY;
                gameStateTime = totalTime;
            }
            else if (event.key.code == Keyboard::Return && gameState == TUTORIAL)
            {
                gameState = PLAY;
                gameStateTime = totalTime;
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

    if (gameState == TUTORIAL)
    {
        tutorialState();
    }
    else if (gameState == PLAY)
    {
        playState();
    }
    else if (gameState == READ)
    {
        readState();
    }

    //screenshots!
    if (Keyboard::isKeyPressed(Keyboard::F11))
    {
        Image Screen = window->capture();
        Screen.saveToFile("screenshot.png");
    }

    frame++;
}

void Game::tutorialState()
{
    //nothing to do here, move along
}

void Game::playState()
{
    totalPlayStateTime += dt;

    //Create systems
    int renderDistance = 2000;
    Vector2f     topLeftVisible(view.getCenter().x - windowWidth / 2 - renderDistance, view.getCenter().y - windowHeight / 2 - renderDistance);
    Vector2f bottomRightVisible(view.getCenter().x + windowWidth / 2 + renderDistance, view.getCenter().y + windowHeight / 2 + renderDistance);
    Vector2f topLeftSystemTile;
    topLeftSystemTile.x = ((int)topLeftVisible.x - (int)topLeftVisible.x % 512) / 512;
    topLeftSystemTile.y = ((int)topLeftVisible.y - (int)topLeftVisible.y % 512) / 512;
    Vector2f bottomRightSystemTile;
    bottomRightSystemTile.x = ((int)bottomRightVisible.x - (int)bottomRightVisible.x % 512) / 512;
    bottomRightSystemTile.y = ((int)bottomRightVisible.y - (int)bottomRightVisible.y % 512) / 512;

    for (int y = topLeftSystemTile.y; y < bottomRightSystemTile.y; y++)
    {
        for (int x = topLeftSystemTile.x; x < bottomRightSystemTile.x; x++)
        {
            if (randint(0, 13, x * y) == 0)
            {
                Vector2f newSystemPosition;
                newSystemPosition.x = x * 512 + randint(-256, 256, x * y);
                newSystemPosition.y = y * 512 + randint(-256, 256, x ^ y);

                bool locationAvailable = true;
                for (int i = 0; i < systems.size(); i++)
                {
                    if (systems.at(i).getPosition() == newSystemPosition)
                    {
                        locationAvailable = false;
                        break;
                    }
                    else
                    {
                        continue;
                    }

                }
                if (locationAvailable)
                    systems.push_back(SolarSystem(Vector2f(newSystemPosition.x, newSystemPosition.y), &data));
            }
        }
    }

    //Delete systems
    Vector2f topLeftDestroy = topLeftVisible;
    topLeftDestroy.x -= 250;
    topLeftDestroy.y -= 250;
    Vector2f bottomRightDestroy = bottomRightVisible;
    bottomRightDestroy.x -= 250;
    bottomRightDestroy.y -= 250;

    for (int i = systems.size() - 1; i >= 0; i--)
    {
        Vector2f systemPos = systems.at(i).getPosition();
        if (!((systemPos.x > topLeftDestroy.x && systemPos.y > topLeftDestroy.y) && (systemPos.x < bottomRightDestroy.x && systemPos.y < bottomRightDestroy.y)))
        {
            systems.erase(systems.begin() + i);
        }
    }


    if (Keyboard::isKeyPressed(Keyboard::F3))
        std::cout << "SysNum:" << systems.size() << ", FPS:" << 1.0 / dt.asSeconds() << ", X:" << player.getPosition().x << ", Y:" << player.getPosition().y
                  << ", dstX:" << topLeftDestroy.x << ", dstY:" << topLeftDestroy.y << "\n";

    //Update objects
    player.update(dt);
    //testSystem.update(dt);
    for (int i = 0; i < systems.size(); i++)
    {
        systems.at(i).update(totalPlayStateTime);
    }
}

void Game::readState()
{

}

void Game::draw()
{
    window->clear(Color(0, 6, 34));

    //Set the view
    drawBackground();

    if (gameState == PLAY || gameState == READ || gameState == TUTORIAL)
    {
        Vector2f roundedPosition;
        roundedPosition.x = (int)player.getPosition().x;
        roundedPosition.y = (int)player.getPosition().y;

        view.setCenter(roundedPosition);
        view.setSize(windowWidth, windowHeight);

        if (Keyboard::isKeyPressed(Keyboard::Comma))
        {
            view.zoom(0.5);
        }
        if (Keyboard::isKeyPressed(Keyboard::Period))
        {
            view.zoom(0.125);
        }

        window->setView(view);

        hudColor = radar ? GREEN : WHITE;

        //Draw all the objects
        for (int i = 0; i < systems.size(); i++)
        {
            systems.at(i).draw(window, useTexture, hudColor);
        }
        player.draw(window, useTexture, hudColor);

        if (radar)
            drawHUD();
    }
    if (gameState == READ && gameState != PLAY)
    {
        drawReadState("planet");
    }
    if (gameState == TUTORIAL)
    {
        drawReadState("tutorial");
    }

    //FPS
    //drawString(window, std::to_string(1 / dt.asSeconds()), Vector2f(player.getPosition().x - windowWidth / 2, player.getPosition().y - windowHeight / 2), &fontTexture, Color(0, 200, 0), 1000);

    window->display();
}

void Game::drawBackground()
{
    //Draw the background
    Sprite background;
    background.setTexture(*useTexture);
    Vector2f topLeftTile;// = player.getPosition() - (Vector2f(windowWidth, windowHeight) / 2.0f);

    topLeftTile.x = (int)(player.getPosition().x - windowWidth / 2.0f);
    topLeftTile.x = topLeftTile.x - (int)topLeftTile.x % 16 - 16;

    topLeftTile.y = (int)(player.getPosition().y - windowHeight / 2.0f);
    topLeftTile.y = topLeftTile.y - (int)topLeftTile.y % 16 - 16;

    for (int y = -3; y < (int)(windowHeight / 16.0) + 3; y++)
    {
        for (int x = -3; x < (int)(windowWidth / 16.0) + 3; x++)
        {
            background.setTextureRect(IntRect(randint(0, 7, ((int)(y + topLeftTile.y / 16) % 4096 + 65536) * ((int)(x + topLeftTile.x / 16) % 4096 + 65536)) * 16, 64, 16, 16));
            background.setPosition(x * 16 + topLeftTile.x, y * 16 + topLeftTile.y);
            background.setColor(hudColor);
            window->draw(background);
        }
    }
}

void Game::drawReadState(std::string entry)
{
    std::string name = "NoNameAssigned";

    if (entry == "planet")
    {
        entry = systems.at(entrySystemIndex).getPlanets()->at(entryPlanetIndex).getEntry();
        name = systems.at(entrySystemIndex).getPlanets()->at(entryPlanetIndex).getName();
    }
    else if (entry == "tutorial")
        entry = "WELCOME TO SPACE.& & CONTROLS:&   -WASD: FLY AROUND&   -ENTER: TOGGLE RADAR&   -APPROACH PLANETS AND PRESS SPACE    TO VIEW INFORMATION ABOUT THEM    WHILE THE RADAR IS ON.& & PRESS ENTER TO START EXPLORING.";

    Vector2f maxEntrySize(281, 394);

    Vector2f textPos = Vector2f(player.getPosition().x - (maxEntrySize.x / 2 - 10), player.getPosition().y - (maxEntrySize.y / 2 - 10));

    int entryHeight = (totalTime.asMilliseconds() - gameStateTime.asMilliseconds()) * 3;
    entryHeight = entryHeight > maxEntrySize.y ? maxEntrySize.y : entryHeight;
    RectangleShape bgRect(Vector2f(maxEntrySize.x, entryHeight));
    bgRect.setOutlineColor(Color(0, 200, 0));
    bgRect.setOutlineThickness(1);
    bgRect.setFillColor(Color(0, 0, 0, 192));
    bgRect.setOrigin(bgRect.getSize().x / 2, bgRect.getSize().y / 2);
    bgRect.setPosition(player.getPosition());
    window->draw(bgRect);
    RectangleShape doubleBorder(Vector2f(maxEntrySize.x - 4, entryHeight - 4));
    doubleBorder.setOutlineColor(Color(0, 200, 0));
    doubleBorder.setOutlineThickness(1);
    doubleBorder.setFillColor(Color(0, 0, 0, 0));
    doubleBorder.setOrigin(doubleBorder.getSize().x / 2, doubleBorder.getSize().y / 2);
    doubleBorder.setPosition(player.getPosition());
    window->draw(doubleBorder);

    //display system[systenentryindex].planets[planetindex].gettext
    //drawString(window, name, player.getPosition(), &fontTexture, Color(0, 200, 0), 100);

    if (totalTime.asMilliseconds() - gameStateTime.asMilliseconds() > 250)
    {
        std::string stringToBeDrawn = "";

        int typedLetters = (int)((totalTime.asMilliseconds() - gameStateTime.asMilliseconds()) / 5);
        typedLetters = typedLetters > entry.size() ? entry.size() : typedLetters;
        for (int i = 0; i < typedLetters; i++)
        {
            stringToBeDrawn += entry[i];
        }

        drawString(window, stringToBeDrawn, textPos, &fontTexture, Color(0, 200, 0), 34);
    }
}

void Game::drawText()
{
    for (int i = 0; i < systems.size(); i++)
    {
        std::string text = "X:" + std::to_string((int)systems.at(i).getPosition().x) + ", Y:" + std::to_string((int)systems.at(i).getPosition().y);
        Vector2f drawPos(systems.at(i).getPosition().x + 20, systems.at(i).getPosition().y - 20);

        drawTag(text, drawPos, Color(0, 255, 0, 128));

        /*std::vector<Planet>* planets = systems.at(i).getPlanets();
        for (int j = 0; j < planets->size(); j++)
        {
            std::string text = "X:" + std::to_string((int)(planets->at(j).getPosition().x)) +
                               ", Y:" + std::to_string((int)(planets->at(j).getPosition().y));
            Vector2f drawPos(planets->at(j).getPosition().x + 10, planets->at(j).getPosition().y - 10);
            //drawTag(text, drawPos, Color(0, 255, 0, 128));
        }*/
    }

    std::string text = "X:" + std::to_string((int)player.getPosition().x) + ", Y:" + std::to_string((int)player.getPosition().y);
    Vector2f drawPos(player.getPosition().x + 12, player.getPosition().y - 12);
    drawTag(text, drawPos, Color(0, 255, 0, 128));
}

void Game::drawTag(std::string text, Vector2f position, Color color)
{
    RectangleShape bg(Vector2f(text.length() * 6 + 3, 7 + 4));
    bg.setPosition(Vector2f((int)(position.x + 3), (int)(position.y - 2)));
    bg.setOutlineThickness(1);
    bg.setOutlineColor(color);
    bg.setFillColor(Color(0, 0, 0, 128));
    window->draw(bg);

    Vector2f textPos((int)(position.x), (int)(position.y));
    drawString(window, text, textPos, &fontTexture, color, -1);
}

void Game::drawHUD()
{
    //coords etc
    drawText();

    //circle thing that is supposed to look like a radar
    int maxRadius = 255;
    int radarOpacity = 256 - ((float)radarRadius / (float)maxRadius) * 255;
    CircleShape radarCircle;

    radarCircle.setFillColor(Color(0, 0, 0, 0));
    radarCircle.setOutlineThickness(1);
    radarCircle.setOutlineColor(Color(0, 200, 0, radarOpacity));
    radarCircle.setPosition(player.getPosition().x - radarRadius,
                            player.getPosition().y - radarRadius);
    radarCircle.setRadius(radarRadius);
    window->draw(radarCircle);

    radarRadius = radarRadius > maxRadius ? 0 : radarRadius + 4;

    //planet guide entry popup
    entryPopupPos = Vector2f(65536, 0);
    for (int j = 0; j < systems.size(); j++)
    {
        std::vector<Planet>* planets = systems.at(j).getPlanets();
        for (int i = 0; i < planets->size(); i++)
        {
            if (getDistance(planets->at(i).getPosition(), player.getPosition()) < 15)
            {
                entrySystemIndex = j;
                entryPlanetIndex = i;
                entryPopupPos = planets->at(i).getPosition();
            }
        }
    }
    Sprite entryPopup;
    entryPopup.setPosition(entryPopupPos);
    entryPopup.setColor(Color(0, 200, 0));
    entryPopup.setTexture(*useTexture);
    entryPopup.setTextureRect(IntRect(0, 48, 16, 16));
    celShade(entryPopup, window, Color(0, 0, 0));
    window->draw(entryPopup);
}

void Game::loadTextures()
{
    if (!myTextureAtlas.loadFromFile("dontReplaceThis.png"))
        window->close();
    if (!someonesTextureAtlas.loadFromFile("replaceThis.png"))
        window->close();
    if (!fontTexture.loadFromFile("font.png"))
        window->close();
}

void Game::loadMusic()
{
    if (!backgroundMusic.openFromFile("Launchpad.ogg"))
        window->close();
}

void Game::loadTextFile(std::string filename, std::vector<std::string>* outputList)
{
    std::ifstream file(filename);

    while(!file.eof())
    {
        std::string line;
        std::getline(file, line);
        if (line.length() > 1)
            outputList->push_back(line);

    }
    std::cout << outputList->size() << " " << outputList->at(0) << "\n";
    file.close();
}

float Game::getDistance(Vector2f point1, Vector2f point2)
{
    float xdistance = fabs(point1.x - point2.x);
    float ydistance = fabs(point1.y - point2.y);
    return (float)sqrt(xdistance * xdistance + ydistance * ydistance);
}
