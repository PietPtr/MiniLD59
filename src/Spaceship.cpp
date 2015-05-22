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
        float extraVelocity = 0.05;
        float slowDown = 2;

        if (Keyboard::isKeyPressed(Keyboard::S))
            velocity.y += extraVelocity;
        else if (velocity.y > 0)
            velocity.y -= extraVelocity * slowDown;

        if (Keyboard::isKeyPressed(Keyboard::W))
            velocity.y -= extraVelocity;
        else if (velocity.y < 0)
            velocity.y += extraVelocity * slowDown;

        if (Keyboard::isKeyPressed(Keyboard::D))
            velocity.x += extraVelocity;
        else if (velocity.x > 0)
            velocity.x -= extraVelocity * slowDown;

        if (Keyboard::isKeyPressed(Keyboard::A))
            velocity.x -= extraVelocity;
        else if (velocity.x < 0)
            velocity.x += extraVelocity * slowDown;
    }
    ///*
    if (!Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S) && fabs(velocity.y) < 0.1)
        velocity.y = 0;
    if (!Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D) && fabs(velocity.x) < 0.1)
        velocity.x = 0;

    //Capping
    int maxSpeed = 4;

    velocity.x = velocity.x > maxSpeed ? maxSpeed : velocity.x;
    velocity.x = velocity.x <-maxSpeed ?-maxSpeed : velocity.x;
    velocity.y = velocity.y > maxSpeed ? maxSpeed : velocity.y;
    velocity.y = velocity.y <-maxSpeed ?-maxSpeed : velocity.y;

    position.x += velocity.x * speed * dt.asSeconds();
    position.y += velocity.y * speed * dt.asSeconds();

    if (velocity.x != 0 || velocity.y != 0)
        rotation = (atan2(velocity.y, velocity.x) * 180 / 3.141592653) - 90;
    //std::cout << fabs(velocity.x) << " <- X      " << fabs(velocity.y) << " <- Y\n";
}

void Spaceship::draw(RenderWindow* window, Texture* texture, Color color)
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

    spaceShipSprite.setColor(color);
    celShade(spaceShipSprite, window, Color(0, 0, 0));
    window->draw(spaceShipSprite);
}
