#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

using namespace sf;

enum Ship { PLAYER, CIVILIAN, ENEMY };

class Spaceship : public GameObject
{
    public:
        Spaceship(Ship _category, Vector2f position, float speed);
        void update(Time dt);
        void draw(RenderWindow* window, Texture* texture);

        Vector2f getPosition() { return position; }
    protected:
    private:
        Ship shipCategory = CIVILIAN;
        Vector2f position;
        Vector2f velocity;
        float speed = 500;
        float rotation = 0;
        IntRect playerSpriteRect {0, 0, 16, 16};
        IntRect civilianSpriteRect {0, 16, 16, 16};
        IntRect enemySpriteRect {0, 32, 16, 16};
        bool usesController = Joystick::isConnected(0);
};

#endif // SPACESHIP_H
