#include <SFML/Graphics.hpp>
#include <iostream>
#include "Spaceship.h"
#include "Planet.h"
#include "SolarSystem.h"

#define GREEN Color(0, 200, 0)
#define WHITE Color(255, 255, 255)

using namespace sf;

class Game
{
    public:
        Game(RenderWindow* window);
        void update();
        void draw();
        void drawText();
        void drawBackground();
        void drawHUD();
        void loadTextures();
        void drawTag(std::string text, Vector2f position, Color color);
        float getDistance(Vector2f point1, Vector2f point2);
        Time getTotalTime() { return totalTime; };
    protected:
    private:
        RenderWindow* window = nullptr;
        Texture myTextureAtlas;
        Texture someonesTextureAtlas;
        Texture* useTexture = &someonesTextureAtlas;
        Texture fontTexture;
        int frame = 0;
        int windowWidth = 1280;
        int windowHeight = 720;
        Spaceship player {PLAYER, Vector2f(-1024, -1800), 400.0f};
        Clock clock;
        Time dt;
        Time totalTime;
        View view;
        bool radar = false;
        int radarRadius = 0;
        Color hudColor = radar ? GREEN : WHITE;

        std::vector <SolarSystem> systems;
};
