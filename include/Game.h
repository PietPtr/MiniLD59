#include <SFML/Graphics.hpp>
#include <iostream>
#include "Spaceship.h"
#include "Planet.h"
#include "SolarSystem.h"

using namespace sf;

class Game
{
    public:
        Game(RenderWindow* window);
        void update();
        void draw();
        void loadTextures();
        Time getTotalTime() { return totalTime; };
    protected:
    private:
        RenderWindow* window = nullptr;
        Texture myTextureAtlas;
        Texture someonesTextureAtlas;
        int frame = 0;
        int windowWidth = 1280;
        int windowHeight = 720;
        Spaceship player {PLAYER, Vector2f(2100, 1050), 400.0f};
        Clock clock;
        Time dt;
        Time totalTime;
        View view;

        std::vector <SolarSystem> systems;
};
