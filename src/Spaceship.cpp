#include "Spaceship.h"
#include <math.h>
#include <iostream>

void celShade(Sprite sprite, RenderWindow* window, Color shadeColor);

Spaceship::Spaceship(Ship _category, Vector2f _position, float _speed)
{
    shipCategory = _category;
    position = _position;
    speed = _speed;
}

void Spaceship::update(Time dt)
{
    //input
    if (shipCategory == PLAYER)
    {
        int deadzone = 20;
        float extraVelocity = 0.05;
        float velocityDevider = 1000;

        if (Keyboard::isKeyPressed(Keyboard::S))
            velocity.y += extraVelocity;
        else if (Joystick::getAxisPosition(0, Joystick::Y) > 0 + deadzone)
            velocity.y += (Joystick::getAxisPosition(0, Joystick::Y)) / velocityDevider;
        else if (velocity.y > 0)
            velocity.y -= extraVelocity;

        if (Keyboard::isKeyPressed(Keyboard::W))
            velocity.y -= extraVelocity;
        else if (Joystick::getAxisPosition(0, Joystick::Y) < 0 - deadzone)
            velocity.y += (Joystick::getAxisPosition(0, Joystick::Y)) / velocityDevider;
        else if (velocity.y < 0)
            velocity.y += extraVelocity;

        if (Keyboard::isKeyPressed(Keyboard::D))
            velocity.x += extraVelocity;
        else if (Joystick::getAxisPosition(0, Joystick::X) > 0 + deadzone)
            velocity.x += (Joystick::getAxisPosition(0, Joystick::X)) / velocityDevider;
        else if (velocity.x > 0)
            velocity.x -= extraVelocity;

        if (Keyboard::isKeyPressed(Keyboard::A))
            velocity.x -= extraVelocity;
        else if (Joystick::getAxisPosition(0, Joystick::X) < 0 - deadzone)
            velocity.x += (Joystick::getAxisPosition(0, Joystick::X)) / velocityDevider;
        else if (velocity.x < 0)
            velocity.x += extraVelocity;
    }
    ///*
    if (fabs(velocity.x) < 0.04)
        velocity.x = 0;
    if (fabs(velocity.y) < 0.04)
        velocity.y = 0;
    //*/

    //Capping
    int maxSpeed = 4;

    velocity.x = velocity.x > maxSpeed ? maxSpeed : velocity.x;
    velocity.x = velocity.x <-maxSpeed ?-maxSpeed : velocity.x;
    velocity.y = velocity.y > maxSpeed ? maxSpeed : velocity.y;
    velocity.y = velocity.y <-maxSpeed ?-maxSpeed : velocity.y;

    position.x += velocity.x * speed * dt.asSeconds();
    position.y += velocity.y * speed * dt.asSeconds();

    rotation = (atan2(velocity.y, velocity.x) * 180 / 3.141592653) - 90;
    //std::cout << fabs(velocity.x) << " <- X      " << fabs(velocity.y) << " <- Y\n";
}

void Spaceship::draw(RenderWindow* window, Texture* texture)
{
    Sprite spaceShipSprite;
    spaceShipSprite.setOrigin(Vector2f(8, 8));
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

    celShade(spaceShipSprite, window, Color(0, 0, 0));
    window->draw(spaceShipSprite);
}
