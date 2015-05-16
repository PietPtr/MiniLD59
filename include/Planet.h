#ifndef PLANET_H
#define PLANET_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

using namespace sf;

enum PlanetName
{
    SATURN,
    JUPITER,
    EARTH,
    VENUS,
    PLUTO,
    NEPTUNE,
    MARS,
    MERCURIUS
};

class Planet : public GameObject
{
    public:
        Planet(int _mass, Vector2f _position);
        void draw(RenderWindow* window, Texture* texture);
        void update(Time dt);
        void setPosition(Vector2f value) { position = value; }
    protected:
    private:
        Vector2f position;
        PlanetName planetName = (PlanetName)0;
        int mass = 0;

        //These values determine the traffic from and to the planet
        int pullFactor = 0;
        int pushFactor = 0;

        Vector2f spritePositions[8] = {Vector2f(32, 80), Vector2f(48, 80), Vector2f(64, 80),
                                       Vector2f(80, 80), Vector2f(96, 80), Vector2f(32, 96),
                                       Vector2f(48, 96), Vector2f(64, 96)};
};


#endif // PLANET_H
