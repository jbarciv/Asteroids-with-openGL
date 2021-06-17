#include "Shape.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Ship.h"
#include "Flame.h"
#include <list>

#ifndef _OBJECTSLIST_H_
#define _OBJECTSLIST_H_

class ObjectsList: list<Shape*>
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
        void remove(Shape* s);
        Ship* getShip();
        int collisions(Bullet* bullet, Ship* ship, float*);
        void reposition(Ship* ship);

};

#endif
