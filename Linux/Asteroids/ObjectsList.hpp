
#include "Asteroid.hpp"
#include "Shape.hpp"
#include "Bullet.hpp"
#include "Ship.hpp"
#include "Flame.hpp"
using namespace std;

#ifndef __OBJECTSLIST_H_
#define __OBJECTSLIST_H_

class ObjectsList: public list<Shape*>
{
    
    private:
        int n;
        Shape* head;
    public:
        Ship* theShip;
    public:
        ObjectsList();
        ~ObjectsList();
        void move();
        void draw();
        void add(Shape* s);
        void removes(Shape* s);
        Ship* getShip();
        int collisions(Bullet* bullet, Ship* ship, float*);
        void reposition(Ship* ship);
};

#endif