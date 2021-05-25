
#include "commonstuff.hpp"
#include "ObjectsList.hpp"
extern int nShips;
extern ObjectsList worldobjects;

ObjectsList::ObjectsList()
{
    Ship *spaceShip;
    worldobjects.push_front(spaceShip);
    for(int i=0 ; i < NUMASTEROIDS; i++)
    {
        Asteroid *asteroid;
        worldobjects.push_front(asteroid);
    }
}
ObjectsList::~ObjectsList()
{
    worldobjects.clear();
}
void ObjectsList::move()
{
    list<Shape*>::iterator i;
    for(i = worldobjects.begin() ; i != worldobjects.end() ; i++)
        (*i)->move();
}
void ObjectsList::draw()
{
    list<Shape*>::iterator i;
    for(i = worldobjects.begin() ; i != worldobjects.end() ; i++)
        (*i)->draw();
}
void ObjectsList::add(Shape* s)
{
    worldobjects.push_front(s);
}
void ObjectsList::remove(Shape* s)
{
    worldobjects.remove(s);
}
Ship* ObjectsList::getShip()
{
    return theShip;
}
int ObjectsList::collisions(Bullet* bullet, Ship* ship, float*)
{
    return 0;
}
void ObjectsList::reposition(Ship* ship)
{
        
}