#include "Planet.h"
#include <iostream>

using namespace sf;

void celShade(Sprite sprite, RenderWindow* window, Color shadeColor);

Planet::Planet(int _mass, Vector2f position)
{
    mass = _mass;
}

void Planet::update(Time dt)
{

}

void Planet::draw(RenderWindow* window, Texture* texture)
{
    Sprite planetSprite;
    planetSprite.setTexture(*texture);
    planetSprite.setPosition(position);

    Vector2f spritePos;// = Vector2f(spritePositions[(int)planetName].x, spritePositions[(int)planetName].y);
    spritePos.x = spritePositions[(int)planetName].x;
    spritePos.y = spritePositions[(int)planetName].y;

    planetSprite.setTextureRect(IntRect(spritePos.x, spritePos.y, 16, 16));

    celShade(planetSprite, window, Color(0, 0, 0));
    window->draw(planetSprite);
}

