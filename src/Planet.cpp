#include "Planet.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace sf;

void celShade(Sprite sprite, RenderWindow* window, Color shadeColor);
int randint(int low, int high, int seed);

Planet::Planet(float _circulationSpeed, float _radius, PlanetName _planetName, dataLists* _dataptr, Vector2f _systemPos)
{
    circulationSpeed = _circulationSpeed;
    radius = _radius;
    planetName = _planetName;
    dataptr = _dataptr;
    systemPosition = _systemPos;
    genSeed = (int)(systemPosition.x + systemPosition.y + radius);

    name = generatePlanetName(dataptr->names);
    entry = generatePlanetEntry();
}

void Planet::update(Time dt)
{
    circulationPosition += circulationSpeed * dt.asSeconds();
}

void Planet::draw(RenderWindow* window, Texture* texture, Color color)
{
    Sprite planetSprite;
    planetSprite.setTexture(*texture);
    planetSprite.setOrigin(Vector2f(8, 8));
    planetSprite.setPosition(position);

    Vector2f spritePos;// = Vector2f(spritePositions[(int)planetName].x, spritePositions[(int)planetName].y);
    spritePos.x = spritePositions[(int)planetName].x;
    spritePos.y = spritePositions[(int)planetName].y;

    planetSprite.setTextureRect(IntRect(spritePos.x, spritePos.y, 16, 16));
    planetSprite.setColor(color);

    celShade(planetSprite, window, Color(0, 0, 0));
    window->draw(planetSprite);
}


std::string Planet::generatePlanetName(std::vector<std::string>* baseNames)
{
    int nameLength = randint(1, 4, genSeed);

    std::string romanNumerals[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X" };

    std::string generatedName = "";

    for (int i = 0; i < nameLength; i++)
    {
        std::string nameToAdd = baseNames->at(randint(0, baseNames->size() - 1, genSeed+i));
        if (nameToAdd != "")
            generatedName += nameToAdd + " ";
    }

    generatedName += romanNumerals[randint(0, 9, genSeed)];

    return generatedName;
}

std::string Planet::generatePlanetEntry()
{
    std::string entry = "NOT GENERATED";
    std::string base = "";
    if (planetName == MERCURIUS || planetName == VENUS || planetName == EARTH || planetName == MARS || planetName == PLUTO)
        base = dataptr->rockPlanetSentences->at(randint(0, dataptr->rockPlanetSentences->size() - 1, genSeed));
    else
        base = name;

    return name + "& & " + std::to_string(planetName);
}





















