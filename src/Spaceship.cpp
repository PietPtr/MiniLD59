#include "Spaceship.h"
#include <math.h>
#include <iostream>

Spaceship::Spaceship(Ship _category, Vector2f _position, float _speed)
{
    shipCategory = _category;
    position = _position;
    speed = _speed;
}

void Spaceship::update()
{
    //input
    if (shipCategory == PLAYER)
    {
        int deadzone = 20;
        float extraVelocity = 0.01;

        if (Keyboard::isKeyPressed(Keyboard::S))
            velocity.y += extraVelocity;
        else if (Joystick::getAxisPosition(0, Joystick::Y) > 0 + deadzone)
            velocity.y = (Joystick::getAxisPosition(0, Joystick::Y) / 100.0);
        else if (velocity.y > 0)
            velocity.y /= 1.1;

        if (Keyboard::isKeyPressed(Keyboard::W))
            velocity.y -= extraVelocity;
        else if (Joystick::getAxisPosition(0, Joystick::Y) < 0 - deadzone)
            velocity.y = (Joystick::getAxisPosition(0, Joystick::Y) / 100.0);
        else if (velocity.y < 0)
            velocity.y /= 1.1;

        if (Keyboard::isKeyPressed(Keyboard::D))
            velocity.x += extraVelocity;
        else if (Joystick::getAxisPosition(0, Joystick::X) > 0 + deadzone)
            velocity.x = (Joystick::getAxisPosition(0, Joystick::X) / 100.0);
        else if (velocity.x > 0)
            velocity.x /= 1.1;

        if (Keyboard::isKeyPressed(Keyboard::A))
            velocity.x -= extraVelocity;
        else if (Joystick::getAxisPosition(0, Joystick::X) < 0 - deadzone)
            velocity.x = (Joystick::getAxisPosition(0, Joystick::X) / 100.0);
        else if (velocity.x < 0)
            velocity.x /= 1.1;
    }

    position.x += velocity.x * speed;
    position.y += velocity.y * speed;

    rotation = (atan2(velocity.y, velocity.x) * 180 / 3.141592653) - 90;
    //std::cout << velocity.x << " <- X      " << velocity.y << " <- Y\n";
}

void Spaceship::draw(RenderWindow* window, Texture* texture)
{
    Sprite spaceShipSprite;
    spaceShipSprite.setTexture(*texture);
    spaceShipSprite.setPosition(position);
    spaceShipSprite.setRotation(rotation);

    switch (shipCategory)
    {
    case (PLAYER):
        spaceShipSprite.setTextureRect(playerSpriteRect);
        break;
    case (CIVILIAN):
        spaceShipSprite.setTextureRect(civilianSpriteRect);
        break;
    case (ENEMY):
        spaceShipSprite.setTextureRect(enemySpriteRect);
        break;
    }

    window->draw(spaceShipSprite);
}
