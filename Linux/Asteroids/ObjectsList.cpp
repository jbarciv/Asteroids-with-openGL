
#include "commonstuff.hpp"
#include "ObjectsList.hpp"
using namespace std;

extern int nShips;
extern ObjectsList worldobjects;

ObjectsList::ObjectsList()
{
    Ship *theShip= new Ship;
    worldobjects.push_front(theShip);
    for(int i=0 ; i < NUMASTEROIDS; i++)
    {
        Asteroid *asteroid = new Asteroid(1);
        worldobjects.push_front(asteroid);
    }
}
ObjectsList::~ObjectsList()
{
    worldobjects.clear();
}
void ObjectsList::move()
{
    cout << "entro en ObjectsList::move " << endl;
    list<Shape*>::iterator i;
    for(i = worldobjects.begin() ; i != worldobjects.end() ; i++)
        (*i)->move();
}
void ObjectsList::draw()
{
    cout << "Entro en draw" << endl;
   
    list<Shape*>::iterator i;
    for(i = worldobjects.begin() ; i != worldobjects.end() ; i++)
    {
        cout << "before (*i)->draw();" << endl;
        (*i)->draw();
        cout << "after (*i)->draw();" << endl;
    }
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