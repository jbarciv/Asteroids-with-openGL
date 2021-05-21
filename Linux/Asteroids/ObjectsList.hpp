 
#include "Shape.hpp"
#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Ship.hpp"
#include "Flame.hpp"

class ObjectList{
    private:
        int n;
        nodo* head;
    public:
        Ship* theShip;
    public:
        ObjectList();
        ~ObjectList();
        void move();
        void draw();
        void add(Shape* s);
        void remove(Shape* s);
        Ship* getShip();
        int collision(Bullet* bullet, Ship* ship, float*);
        void reposition(Ship* ship);
};