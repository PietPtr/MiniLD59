#include "SolarSystem.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

#define TO_DEGREES_MULT 5729577951

using namespace sf;

void celShade(Sprite sprite, RenderWindow* window, Color shadeColor);
int randint(int low, int high, int seed);
int randint(int low, int high);

SolarSystem::SolarSystem(Vector2f _position, dataLists* _dataptr)
{
    position = _position;
    dataptr = _dataptr;
    generateSystem();
}

void SolarSystem::update(Time totalTime)
{
    for (int i = 0; i < planets.size(); i++)
    {
        planets.at(i).update(totalTime);
    }

    asteroidRotation = asteroidSpeed * totalTime.asSeconds();
}

void SolarSystem::draw(RenderWindow* window, Texture* texture, Color color)
{
    Sprite starSprite;
    starSprite.setTexture(*texture);

    //Star
    if (starType == REDDWARF)
    {
        starSprite.setTextureRect(IntRect(80, 96, 16, 16));
        starSprite.setOrigin(Vector2f(8, 8));
        starSprite.setPosition(position);
    }
    else if (starType == SUNLIKE)
    {
        starSprite.setTextureRect(IntRect(0, 80, 32, 32));
        starSprite.setOrigin(Vector2f(16, 16));
        starSprite.setPosition(position);
    }

    starSprite.setColor(color);
    celShade(starSprite, window, Color(0, 0, 0));
    window->draw(starSprite);

    //planets
    for (int i = 0; i < planets.size(); i++)
    {
        Vector2f planetPos;
        float angle = planets.at(i).getCirculationPosition();
        float radius = planets.at(i).getRadius();
        planetPos.x = (cos((float)angle)) * (float)radius;
        planetPos.y = (sin((float)angle)) * (float)radius;

        planets.at(i).setPosition(planetPos + position);

        planets.at(i).draw(window, texture, color);
    }

    //Asteroids
    if (asteroidBelt > 0)
    {
        for (int i = 0; i < asteroidBelt; i++)
        {
            Sprite asteroidSprite;
            asteroidSprite.setTexture(*texture);
            asteroidSprite.setTextureRect(IntRect(randint(0, 7, i) * 16, 112, 32, 32));

            float angle = asteroidRotation + (i);
            float radius = asteroidBelt + randint(20, 60, i);
            Vector2f asteroidPos;
            asteroidPos.x = (cos((float)angle)) * (float)radius;
            asteroidPos.y = (sin((float)angle)) * (float)radius;

            asteroidSprite.setOrigin(Vector2f(8, 8));
            asteroidSprite.setPosition(asteroidPos + position);

            asteroidSprite.setColor(color);
            celShade(asteroidSprite, window, Color(0, 0, 0));
            window->draw(asteroidSprite);
        }
    }
}

void SolarSystem::generateSystem()
{
    int genSeed = position.x * position.y;

    int randomStar = randint(0, 1000, genSeed*2);

    if (randomStar > 500)
        starType = REDDWARF;
    else
        starType = SUNLIKE;

    if (starType == REDDWARF)
    {
        generateNear(genSeed, 2, 8);

        //std::cout << "Red dwarf system, " << planets.size() << " planets at X:" << position.x << ", Y:" << position.y << "\n";
    }
    else if (starType == SUNLIKE)
    {
        generateNear(genSeed, 1, 5);
        generateGas(genSeed);

        if (randint(0, 3, genSeed) != 1) //25% percent change on asteroid belt
            asteroidBelt = planets.back().getRadius() + randint(50, 100), genSeed;

        //std::cout << "Sunlike system, " << planets.size() << " planets, asteroid ring at " << asteroidBelt << " KM at X:" << position.x << ", Y:" << position.y << "\n";
    }
    //std::cout << "seed:" << genSeed << "\n";
}

void SolarSystem::generateNear(int genSeed, int minPlanets, int maxPlanets)
{
    int amountOfNearPlanets = randint(minPlanets, maxPlanets, genSeed*3);
    for (int i = 1; i <= amountOfNearPlanets; i++)
    {
        planets.push_back(Planet(randint(2000, 6000, genSeed*i*4) / 10000.0f, i * randint(19, 25, genSeed*i*5), (PlanetName)(randint(0, 4, genSeed*i*7)), dataptr, position));
    }

}

void SolarSystem::generateGas(int genSeed)
{
    int amountOfGasPlanets = randint(1, 4, genSeed);
    int amountOfNearPlanets = planets.size();
    for (int i = 1; i <= amountOfGasPlanets; i++)
    {
        planets.push_back(Planet(randint(100, 600, genSeed*i*4) / 10000.0f, planets.at(amountOfNearPlanets - 1).getRadius() + i * randint(105, 195, genSeed*i*5), (PlanetName)(randint(5, 7, genSeed*i*6)), dataptr, position));
    }
}
