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
        void drawText();
        void loadTextures();
        void drawTag(std::string text, Vector2f position, Color color);
        Time getTotalTime() { return totalTime; };
    protected:
    private:
        RenderWindow* window = nullptr;
        Texture myTextureAtlas;
        Texture someonesTextureAtlas;
        Texture fontTexture;
        int frame = 0;
        int windowWidth = 1280;
        int windowHeight = 720;
        Spaceship player {PLAYER, Vector2f(-1024, -1800), 400.0f};
        Clock clock;
        Time dt;
        Time totalTime;
        View view;
        bool displayHUD = false;

        std::vector <SolarSystem> systems;
};
