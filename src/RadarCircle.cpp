#include <SFML/Graphics.hpp>
#include "RadarCircle.h"

RadarCircle::RadarCircle(Vector2f _position)
{
    position = _position;
}

void RadarCircle::update(Time dt)
{
    radius += dt.asSeconds() * 5;
}

void RadarCircle::draw(RenderWindow* window, Color color)
{
    CircleShape circle;
    circle.setPosition(position);
    circle.setFillColor(Color(0, 0, 0, 0));
    circle.setRadius(radius);
    circle.setOutlineColor(color);
    circle.setOutlineThickness(1);
    window->draw(circle);
}
