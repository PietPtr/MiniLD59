#include <SFML/Graphics.hpp>
#include <iostream>
#include "Spaceship.h"
#include "Planet.h"
#include "SolarSystem.h"
#include "dataLists.h"

#define GREEN Color(0, 200, 0)
#define WHITE Color(255, 255, 255)

using namespace sf;

int randint(int low, int high, int seed);
int randint(int low, int high);

enum GameState {
    TUTORIAL,
    PLAY,
    READ
};



class Game
{
    public:
        Game(RenderWindow* window);
        void update();
        void tutorialState();
        void playState();
        void readState();

        void draw();
        void drawText();
        void drawBackground();
        void drawHUD();
        void drawReadState(std::string entry);
        void drawTag(std::string text, Vector2f position, Color color);

        void loadTextures();
        void loadTextFile(std::string filename, std::vector<std::string>* outputList);

        float getDistance(Vector2f point1, Vector2f point2);
        Time getTotalTime() { return totalTime; };
    protected:
    private:
        RenderWindow* window = nullptr;
        Texture myTextureAtlas;
        Texture someonesTextureAtlas;
        Texture* useTexture = &myTextureAtlas;
        Texture fontTexture;
        int frame = 0;
        int windowWidth = 1280;
        int windowHeight = 720;
        Spaceship player {PLAYER, Vector2f(randint(-1024, 1024), randint(-1024, 1024)), 400.0f};
        Clock clock;
        Time dt;
        Time totalTime;
        Time gameStateTime; //Time when the new gamestate started
        Time totalPlayStateTime;
        View view;
        bool radar = false;
        int radarRadius = 0;
        Color hudColor = radar ? GREEN : WHITE;
        GameState gameState = TUTORIAL;
        Vector2f entryPopupPos {2 ^ 32, 0};
        int entrySystemIndex = -1;
        int entryPlanetIndex = -1;

        std::vector <SolarSystem> systems;
        std::vector <std::string> baseNames;
        std::vector <std::string> rockPlanetSentences;
        std::vector <std::string> gasPlanetSentences;
        std::vector <std::string> traits;
        std::vector <std::string> adjectives;
        std::vector <std::string> nouns;
        std::vector <std::string> people;

        dataLists data;
};
