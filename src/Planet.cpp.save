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
    std::string entry = "";
    std::string base = "";
    if (planetName == MERCURIUS || planetName == VENUS || planetName == EARTH || planetName == MARS || planetName == PLUTO)
        base = dataptr->rockPlanetSentences->at(randint(0, dataptr->rockPlanetSentences->size() - 1, genSeed));
    else
        base = dataptr->gasPlanetSentences->at(randint(0, dataptr->gasPlanetSentences->size() - 1, genSeed));

    entry += name + "& & ";// + base;

    std::string variable;
    bool recordVariable = false;
    //bool addLetterFromBase = true;

    for (int i = 0; i < base.length(); i++)
    {
        if (base[i] == '$')
            recordVariable = true;
        if (base[i] == ' ' || base[i] == ',' || base[i] == '.')
        {
            recordVariable = false;
            std::cout << "'" << variable << "'\n";

            if (variable == "$NAME")
                entry += name;
            else if (variable == "$ADJ")
                entry += dataptr->adjectives->at(randint(0, dataptr->adjectives->size() - 1, genSeed+i));
            else if (variable == "$TRAIT")
                entry += dataptr->traits->at(randint(0, dataptr->traits->size() - 1, genSeed+i));
            else if (variable == "$NOUN")
                entry += dataptr->nouns->at(randint(0, dataptr->nouns->size() - 1, genSeed+i));
            else if (variable == "$PEOPLE")
                entry += dataptr->people->at(randint(0, dataptr->people->size() - 1, genSeed+i));

            variable = "";
        }

        if (recordVariable)
            variable += base[i];
        else
            entry += base[i];
    }

    return "'''''' don't isn't";
}





















