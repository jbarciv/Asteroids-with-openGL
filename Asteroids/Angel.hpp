////////////////////////////////////////
// Angel.hpp                          //
// Class implementation for the Angel //
////////////////////////////////////////

#include "commonstuff.hpp"
#include "Shape.hpp"

class Angel: public Shape{
 private:
    bool status;
    int tamano;
 public:
    Angel();
    ~Angel();
    void setStatus(bool);
    bool getStatus();
    void setSize(int);
    float getSize();
    void draw();
    void teleport();
};

// la idea es que aparezca estatica en algun lugar aleatorio
// y si llevas la nave encima
// y te chocas aumenta en 1 tu vida y te da x puntos pero si la 
// disparas lo destruyes y te quedas sin...