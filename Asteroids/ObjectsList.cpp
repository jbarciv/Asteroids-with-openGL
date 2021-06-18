
#include "commonstuff.hpp"
#include "ObjectsList.hpp"

using namespace std;

extern int nShips;
extern ObjectsList worldobjects;

ObjectsList::ObjectsList()
{   
    n = 0;              // List begins empty
    head = NULL;        // It does not make sense with list< > template
    theShip = new Ship;
    worldobjects.push_front(theShip);

    for(int i=0 ; i < NUMASTEROIDS; i++)
    {
        Asteroid *asteroid = new Asteroid;
        worldobjects.push_front(asteroid);
    }

    theUFO = new Alien; // theUFO is created but not included
    theAngel = new Angel;
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

void ObjectsList::removes(Shape* s)
{
    worldobjects.remove(s);
}

Ship* ObjectsList::getShip()
{
    return theShip;
}

Alien* ObjectsList::getUFO()
{
    return theUFO;
}

 Angel* ObjectsList::getAngel()
 {
     return theAngel;
 }

int ObjectsList::collisions(Bullet* bullet, Ship* ship, Alien* ovni,Angel* angel, float* explos)
{   
    float pos_s[3];
    ship -> getPos(pos_s);
    float size_s = ship->getSize();

    float pos_u[3];
    ovni -> getPos(pos_u);
    float size_u = ovni -> getSize();

    if(mydistance(pos_u[0], pos_u[1], pos_s[0], pos_s[1]) < (size_u + size_s) && ovni->getStatus() == ACTIVE) 
    {
        explos[0] = pos_s[0];
        explos[1] = pos_s[1];
        worldobjects.remove(ship);
        worldobjects.remove(ovni);
        return 6;
    }

    if (bullet)
    {
        float pos_b[3];
        bullet -> getPos(pos_b);
        float size_b = bullet -> getSize();

        if(mydistance(pos_u[0], pos_u[1], pos_b[0], pos_b[1]) < (size_u + size_b) && ovni->getStatus() == ACTIVE)
        {
            worldobjects.removes(ovni);
            ovni -> setStatus(DESTROYED);
            worldobjects.removes(bullet);
            explos[0] = pos_b[0];
            explos[1] = pos_b[1];
            return 5;
        }
    }

    list<Shape*>::iterator i;
    for(i = worldobjects.begin() ; i != worldobjects.end() ; i++)
    {      
        if((*i) == theShip) continue;  // We skip theShip and the bullet
        if((*i) == bullet) continue;
        if((*i) == theUFO) continue;
    
        float pos_a[3];                
        (*i) -> getPos(pos_a);
        float size_a = (*i)->getSize();

        if(mydistance(pos_a[0], pos_a[1], pos_s[0], pos_s[1]) < (size_a + size_s)) 
        {
            explos[0] = pos_s[0];      // Is given to expl_pos the ship position for the explosion
            explos[1] = pos_s[1];
            worldobjects.remove(ship);
            return 1;
        }

        if(bullet)
        {   
            float pos_b[3];
            bullet -> getPos(pos_b);
            float size_b = bullet -> getSize();

            if(mydistance(pos_a[0], pos_a[1], pos_b[0], pos_b[1]) < (size_a + size_b))
            {   
                worldobjects.remove(bullet);
                size_a = size_a / CONSTANT; // The asteroid size needs to be corrected to integer

                if( size_a == SMALL)
                {
                    worldobjects.remove(*i);
                    cout << "ASTEROIDE DESTRUIDO" << endl;
                    explos[0] = pos_a[0];   // Is given to expl_pos the asteroid position for the explosion
                    explos[1] = pos_a[1];
                    return 4;
                } else if(size_a == MEDIUM || size_a == BIG)
                {  
                    Asteroid *x = new Asteroid;     // Cast from Shape* to Asteroid*
                    x = (Asteroid*) (*i);
                    worldobjects.push_front(x->split());
                    
                    explos[0] = pos_a[0];
                    explos[1] = pos_a[1];
                    return (size_a == MEDIUM) ? 2 : 3;
                } 
            } 
        }
    }
    return 0;
}

void ObjectsList::reposition(Ship* ship)
{
    float size_s = ship->getSize();

    list<Shape*>::iterator i;
    for(i = worldobjects.begin() ; i != worldobjects.end() ; i++)
    {      
        if((*i) == theShip) continue;   // We skip theShip and the bullets
        // if((*i) == bullet) continue; pensarlo buen
        

        float pos_a[3];
        (*i) -> getPos(pos_a);
        float size_a = (*i)->getSize();

        if(mydistance(pos_a[0], pos_a[1], 0.0, 0.0) < (size_a + size_s)) 
        {   
            Asteroid *x = new Asteroid;     // Cast from Shape* to Asteroid*
            x = (Asteroid*) (*i);
            x->reposition();            
        }
    }
    worldobjects.push_front(ship);
}