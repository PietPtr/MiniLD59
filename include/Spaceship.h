#include <SFML/Graphics.hpp>

using namespace sf;

enum Ship { PLAYER, CIVILIAN, ENEMY };

class Spaceship
{
    public:
        Spaceship(Ship _category, Vector2f position, float speed);
        //Spaceship();
    protected:
    private:
        Ship shipCategory;
        Vector2f position;
        Vector2f velocity;
        float speed;
};
