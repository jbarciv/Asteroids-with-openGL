/////////////////////////////////////////////////////////////////////
// ObjectsList.cpp                                                 //
// Linked list that manages the objects that interact in the game  //
/////////////////////////////////////////////////////////////////////

#include "commonstuff.hpp"
#include "ObjectsList.hpp"

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

    theUFO = new Alien; // theUFO and theAngel are created but not included
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

int ObjectsList::collisions(Bullet* bullet, Ship* ship, Alien* ovni, Angel* angel, float* explos)
{   
    float pos_s[3];                     // The Ship position is saved in "pos_s" 
    ship -> getPos(pos_s);
    float size_s = ship->getSize();     // The Ship size is saved in "size_s"

    float pos_u[3];                     // The UFO position is saved in "pos_u"
    ovni -> getPos(pos_u);
    float size_u = ovni -> getSize();   // The UFI size is saved in "size_u"

    float pos_an[3];                    // The Angel position is saved in "pos_an"
    angel -> getPos(pos_an);
    float size_an = angel -> getSize(); // The Angel size is saved in "size_an"

    // Collisions between Ship/Asteroids and Bullet/Ateroids are checked
    list<Shape*>::iterator i;
    for(i = worldobjects.begin() ; i != worldobjects.end() ; i++)
    {      
        if((*i) == theShip) continue;  // We skip theShip, bullet, UFObullet, theUFO and theAngel
        if((*i) == bullet) continue;
        if((*i) == theUFO) continue;
        if((*i) == theAngel) continue;
    
        float pos_a[3];                // The current Asteroid position is saved in "pos_a"
        (*i) -> getPos(pos_a);
        float size_a = (*i)->getSize();// The current Asteroid size is saved in "size_a"

        // Checking the distance/collision between the current Asteroid and theShip
        if(mydistance(pos_a[0], pos_a[1], pos_s[0], pos_s[1]) < (size_a + size_s)) 
        {
            explos[0] = pos_s[0];      // Is given to expl_pos the ship position for the explosion
            explos[1] = pos_s[1];
            worldobjects.remove(ship);
            return 1;
        }

        // If there is a bullet the distance/collision between the current Asteroid and the Bullet
        //  is checked
        if(bullet)
        {   
            float pos_b[3];             // The bullet position is saved in "pos_b"
            bullet -> getPos(pos_b);
            float size_b = bullet -> getSize();// The bullet size is saved in "size_b"

            if(mydistance(pos_a[0], pos_a[1], pos_b[0], pos_b[1]) < (size_a + size_b))
            {   
                worldobjects.remove(bullet);
                size_a = size_a / CONSTANT; // The asteroid size needs to be corrected to integer

                if( size_a == SMALL)
                {
                    worldobjects.remove(*i);
                    explos[0] = pos_a[0];   // Is given to expl_pos the asteroid position for the explosion
                    explos[1] = pos_a[1];
                    return 4;
                } else if(size_a == MEDIUM || size_a == BIG)
                {  
                    Asteroid *x = new Asteroid;     // Cast from Shape* to Asteroid*
                    x = (Asteroid*) (*i);
                    // The medium and big asteroids splits into smallers asteroids
                    worldobjects.push_front(x->split());
                    explos[0] = pos_a[0]; // There is again an explosion
                    explos[1] = pos_a[1];
                    return (size_a == MEDIUM) ? 2 : 3;
                } 
            } 
        }
    }

    // Checking the distance/collision between the Ship and theUFO
    if(mydistance(pos_u[0], pos_u[1], pos_s[0], pos_s[1]) < (size_u + size_s) && ovni->getStatus() == ACTIVE) 
    {
        explos[0] = pos_s[0];           // There is explosion
        explos[1] = pos_s[1];
        worldobjects.remove(ship);
        worldobjects.remove(ovni);
        return 5;
    }

    // Checking the distance/collision between the Ship and theAngel
    if(mydistance(pos_an[0], pos_an[1], pos_s[0], pos_s[1]) < (size_an + size_s) && angel->getStatus() == ACTIVE) 
    {
        worldobjects.removes(angel);
        angel -> setStatus(INACTIVE);
        return 6;
    }

    if (bullet)
    {
        float pos_b[3];                    // The bullet position is saved in "pos_b"
        bullet -> getPos(pos_b);
        float size_b = bullet->getSize();// The bullet size is saved in "size_b"

        // Checking the distance/collision between the bullet and theUFO
        if(mydistance(pos_u[0], pos_u[1], pos_b[0], pos_b[1]) < (size_u + size_b) && ovni->getStatus() == ACTIVE)
        {
            explos[0] = pos_u[0];
            explos[1] = pos_u[1];
            worldobjects.removes(bullet);
            worldobjects.removes(ovni);
            ovni -> setStatus(DESTROYED);
            return 7;
        }

        // Checking the distance/collision between the bullet and theAngel
        if(mydistance(pos_an[0], pos_an[1], pos_b[0], pos_b[1]) < (size_an + size_b) && angel->getStatus() == ACTIVE)
        {
            explos[0] = pos_an[0];
            explos[1] = pos_an[1];
            worldobjects.removes(bullet);
            worldobjects.removes(angel);
            angel -> setStatus(INACTIVE);
            return 8;
        }
    }
    return 0; // If there in not any collision
}

void ObjectsList::reposition(Ship* ship, Alien* ovni, Angel* angel)
{
    float pos_s[3];                     // The Ship position is saved in "pos_s" 
    ship -> getPos(pos_s);
    float size_s = ship->getSize();     // The Ship size is saved in "size_s"

    float pos_u[3];                     // The UFO position is saved in "pos_u"
    ovni -> getPos(pos_u);
    float size_u = ovni -> getSize();   // The UFI size is saved in "size_u"

    float pos_an[3];                    // The Angel position is saved in "pos_an"
    angel -> getPos(pos_an);
    float size_an = angel -> getSize(); // The Angel size is saved in "size_an"

    list<Shape*>::iterator i;
    for(i = worldobjects.begin() ; i != worldobjects.end() ; i++)
    {      
        if((*i) == theShip) continue;   // We skip theShip and the bullets
        
        float pos_a[3];
        (*i) -> getPos(pos_a);
        float size_a = (*i)->getSize();

        if((*i) == theUFO)
        {   
            if(mydistance(pos_u[0], pos_u[1], 0.0, 0.0) < (size_u + size_s) && ovni->getStatus() == ACTIVE)
            {
                Alien *x = new Alien;     // Cast from Shape* to Alien*
                x = (Alien*) (*i);
                x->reposition();
            }
        }

        if((*i) == theAngel)
        {
            if(mydistance(pos_an[0], pos_an[1], 0.0, 0.0) < (size_an + size_s) && angel->getStatus() == ACTIVE)
            {
                Angel *x = new Angel;     // Cast from Shape* to Alien*
                x = (Angel*) (*i);
                x->reposition();
            }
        }

        if(mydistance(pos_a[0], pos_a[1], 0.0, 0.0) < (size_a + size_s)) 
        {   
            Asteroid *x = new Asteroid;     // Cast from Shape* to Asteroid*
            x = (Asteroid*) (*i);
            x->reposition();            
        }
    }
    worldobjects.push_front(ship);
}