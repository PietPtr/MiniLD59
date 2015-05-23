#ifndef PLANET_H
#define PLANET_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"

using namespace sf;

int randint(int low, int high);

enum PlanetName
{
    MERCURIUS,
    VENUS,
    EARTH,
    MARS,
    PLUTO,
    JUPITER,
    SATURN,
    NEPTUNE
};

class Planet : public GameObject
{
    public:
        Planet(float _circulationSpeed, float _radius, PlanetName _planetName, std::vector<std::string>* _baseNames, Vector2f _systemPos);
        void draw(RenderWindow* window, Texture* texture, Color color);
        void update(Time dt);
        void setPosition(Vector2f value) { position = value; }
        float getRadius() { return radius; }
        float getCirculationPosition() { return circulationPosition; }
        std::string generatePlanetEntry();
        std::string generatePlanetName(std::vector<std::string>* _baseNames);
        std::string getName() { return name; }
        std::string getEntry() { return entry; }
        Vector2f getPosition() { return position; }
        void setBaseNameptr(std::vector<std::string>* ptr) { baseNames = ptr; }
    protected:
    private:
        Vector2f systemPosition; //Used in the seed for random text/name generation
        Vector2f position;
        PlanetName planetName = (PlanetName)0;

        //These values determine the traffic from and to the planet
        int pullFactor = 0;
        int pushFactor = 0;

        float radius = 0;
        float circulationSpeed = 0.1; //radians per second
        float circulationPosition = randint(0, 3);

        Vector2f spritePositions[8] =  {Vector2f(64, 96),  //Mercurius
                                        Vector2f(80, 80),  //Venus
                                        Vector2f(64, 80),  //Earth
                                        Vector2f(48, 96),  //Mars
                                        Vector2f(96, 80),  //Pluto
                                        Vector2f(48, 80),  //Jupiter
                                        Vector2f(32, 80),  //Saturn
                                        Vector2f(32, 96)}; //Neptune

        int genSeed = 0;

        std::string name = "NoNameAssigned";
        std::string entry = "LOREM IPSUM DOLOR SIT AMET, CONSECTETUR ADIPISCING ELIT. NULLAM ELIT LEO, AUCTOR ID ELEIFEND MOLLIS, VOLUTPAT AT ENIM. DONEC EGET CONSECTETUR LOREM. FUSCE NEC PELLENTESQUE LACUS. VESTIBULUM AC DOLOR VITAE JUSTO PORTTITOR FEUGIAT VITAE VEL EX. ALIQUAM JUSTO MI, ACCUMSAN AC JUSTO SIT AMET, ULLAMCORPER MATTIS TELLUS. DONEC CURSUS, DOLOR SED FRINGILLA FRINGILLA, LIGULA NUNC CONGUE FELIS, NON RUTRUM LECTUS SEM ID NISL. INTEGER NEC PLACERAT VELIT. MAECENAS DOLOR ANTE, PRETIUM EGET VARIUS ET, MOLESTIE NEC TELLUS. DONEC VENENATIS NEQUE NEC DIAM AUCTOR GRAVIDA. ETIAM PELLENTESQUE VULPUTATE FACILISIS. NULLAM ID EROS SED MI PORTA BIBENDUM. IN EU MAURIS CONSECTETUR, LUCTUS LECTUS EU, BLANDIT LECTUS. PELLENTESQUE MOLESTIE NISI UT NEQUE TINCIDUNT, ID HENDRERIT TORTOR MATTIS. PHASELLUS A DAPIBUS NISL. SED LIGULA RISUS, CONSECTETUR VEL FACILISIS EU, PLACERAT IN EST. ETIAM QUIS MAXIMUS DIAM, ID POSUERE PURUS. ETIAM GRAVIDA ACCUMSAN METUS, IN CONGUE DOLOR PORTTITOR IN. SED TEMPUS, VELIT SIT AMET FAUCIBUS CONGUE, EROS RISUS PELLENTESQUE ORCI, EGET SAGITTIS LEO LIBERO GRAVIDA SAPIEN. ETIAM VITAE ELIT LEO. MORBI SED ALIQUET ENIM, SED AUCTOR LECTUS. ALIQUAM EUISMOD NISL SED TINCIDUNT AUCTOR. MAECENAS EGESTAS PORTTITOR TELLUS, IN MOLESTIE ARCU ALIQUAM AC. PELLENTESQUE IACULIS, QUAM ET ACCUMSAN EUISMOD, AUGUE FELIS TINCIDUNT ORCI, IN POSUERE NULLA PURUS NEC TURPIS. NULLAM TRISTIQUE URNA NISL, AT MOLESTIE ELIT DAPIBUS IN. CRAS ID TEMPUS LACUS, IN VENENATIS FELIS. CRAS HENDRERIT SAPIEN VEL ELIT VEHICULA SUSCIPIT. DONEC TINCIDUNT VESTIBULUM NISI.";
        std::vector<std::string>* baseNames = nullptr;

};


#endif // PLANET_H
