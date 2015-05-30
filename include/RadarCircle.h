#ifndef RADARCIRCLE_H
#define RADARCIRCLE_H

#include <GameObject.h>


class RadarCircle : public GameObject
{
    public:
        RadarCircle(Vector2f position);
        void update(Time dt);
        void draw(RenderWindow* window, Color color);
        Vector2f Getposition() { return position; }
        void Setposition(Vector2f val) { position = val; }
        int Getradius() { return radius; }
        void Setradius(int val) { radius = val; }
    protected:
    private:
        Vector2f position;
        int radius;
};

#endif // RADARCIRCLE_H
