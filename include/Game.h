#include <SFML/Graphics.hpp>
#include <iostream>
#include "Spaceship.h"

using namespace sf;

class Game
{
    public:
        Game(RenderWindow* window);
        void update();
        void draw();
        void loadTextures();
        int randint(int low, int high, int seed);
    protected:
    private:
        RenderWindow* window;
        Texture myTextureAtlas;
        Texture someonesTextureAtlas;
        int frame;
        int windowWidth;
        int windowHeight;
        Spaceship player {PLAYER, Vector2f(100, 100), 10.0f};
};
