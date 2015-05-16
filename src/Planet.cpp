#include "Planet.h"
#include <iostream>

using namespace sf;

void celShade(Sprite sprite, RenderWindow* window, Color shadeColor);

Planet::Planet(float _circulationSpeed, float _radius, PlanetName _planetName, int _pullFactor, int _pushFactor)
{
    circulationSpeed = _circulationSpeed;
    radius = _radius;
    planetName = _planetName;
    pullFactor = _pullFactor;
    pushFactor = _pushFactor;
}

void Planet::update(Time dt)
{
    circulationPosition += circulationSpeed * dt.asSeconds();
}

void Planet::draw(RenderWindow* window, Texture* texture)
{
    Sprite planetSprite;
    planetSprite.setTexture(*texture);
    planetSprite.setOrigin(Vector2f(8, 8));
    planetSprite.setPosition(position);

    Vector2f spritePos;// = Vector2f(spritePositions[(int)planetName].x, spritePositions[(int)planetName].y);
    spritePos.x = spritePositions[(int)planetName].x;
    spritePos.y = spritePositions[(int)planetName].y;

    planetSprite.setTextureRect(IntRect(spritePos.x, spritePos.y, 16, 16));

    celShade(planetSprite, window, Color(0, 0, 0));
    window->draw(planetSprite);
}

