#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#include "Planet.h"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

enum StarType
{
    SUNLIKE,
    REDDWARF
};

class SolarSystem
{
    public:
        SolarSystem(Vector2f _position);
        void update(Time dt);
        void draw(RenderWindow* window, Texture* texture);
        void generateSystem();
        void generateNear(int genSeed);
        void generateGas(int genSeed);
    protected:
    private:
        std::vector<Planet> planets;
        int asteroidBelt = 0;               //0: no belt, > 0: radius of asteroid belt
        Vector2f position;
        StarType starType = (StarType)0;

};

#endif // SOLARSYSTEM_H
