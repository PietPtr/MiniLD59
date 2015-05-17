#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

using namespace sf;
int main()
{
    srand(time(NULL));

    int windowWidth = 1280;
    int windowHeigth = 720;
    RenderWindow window(VideoMode(windowWidth, windowHeigth), "Float");
    window.setVerticalSyncEnabled(true);

    Game game(&window);

    while (window.isOpen())
    {
        game.update();
        game.draw();
    }

    return 0;
}

void celShade(Sprite sprite, RenderWindow* window, Color shadeColor)
{
    sprite.setColor(shadeColor);
    Vector2f spritePos = sprite.getPosition();
    sprite.setPosition(Vector2f(spritePos.x - 1, spritePos.y));
    window->draw(sprite);
    sprite.setPosition(Vector2f(spritePos.x + 1, spritePos.y));
    window->draw(sprite);
    sprite.setPosition(Vector2f(spritePos.x, spritePos.y - 1));
    window->draw(sprite);
    sprite.setPosition(Vector2f(spritePos.x, spritePos.y + 1));
    window->draw(sprite);
}

int randint(int low, int high, int seed)
{
    srand(seed);
    int value = rand() % (high + 1 - low) + low;
    return value;
}

int randint(int low, int high)
{
    int value = rand() % (high + 1 - low) + low;
    srand(time(NULL) * value * rand());

    return value;
}

void drawString(RenderWindow* window, std::string text, Vector2f position, Texture* fontTexture, Color color)
{
    int drawY = position.y;
    int drawX = position.x;

    int letterWidth = 5;
    int letterHeight = 7;

    for (int i = 0; i < text.length(); i++)
    {
        int num = (int)(text[i]);

        Sprite charSprite;
        charSprite.setTexture(*fontTexture);

        drawX += letterWidth + 1;

        if (num >= 48 && num <= 57)
            charSprite.setTextureRect(IntRect((num - 48) * letterWidth, 0, letterWidth, letterHeight));
        else if (num >= 65 && num <= 90)
            charSprite.setTextureRect(IntRect((num - 55) * letterWidth, 0, letterWidth, letterHeight));
        else if (num >= 97 && num <= 122)
            charSprite.setTextureRect(IntRect((num - 61) * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 58)
            charSprite.setTextureRect(IntRect(62 * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 46)
            charSprite.setTextureRect(IntRect(63 * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 44)
            charSprite.setTextureRect(IntRect(64 * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 32)
            charSprite.setTextureRect(IntRect(66 * letterWidth, 0, letterWidth, letterHeight));
        else if (num == 45)
            charSprite.setTextureRect(IntRect(67 * letterWidth, 0, letterWidth, letterHeight));
        else
            charSprite.setTextureRect(IntRect(65 * letterWidth, 0, letterWidth, letterHeight));

        charSprite.setColor(color);
        charSprite.setPosition(Vector2f(drawX, drawY));
        window->draw(charSprite);
    }
}

std::string floatToString(float flt)
{

}
