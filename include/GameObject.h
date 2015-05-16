#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>

using namespace sf;

class GameObject
{
    public:
        GameObject();
        void update(Time dt);
        void draw(RenderWindow* window, Texture* texture);
    protected:
    private:
};

#endif // GAMEOBJECT_H
