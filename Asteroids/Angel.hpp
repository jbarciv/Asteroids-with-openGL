
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
    void move();
    //void rotate(float,float,float);
    // deberia de cambiar posicion cada x tiempo
   // void resetpos();
};

// la idea es que aparezca estatica en algun lugar aleatorio
// cercano al marco de la ventana y si llevas la nave encima
// y te chocas aumenta en 1 tu vida y te da x puntos pero si la 
// disparas te resta