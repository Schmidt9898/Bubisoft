#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED
#include <cmath>
class Drawable
{
protected:
    float x, y;
    int32_t r;
public:
    Drawable(float pos_x,float pos_y,int32_t size):x(pos_x),y(pos_y),r(size) {}


    virtual ~Drawable();

    virtual bool collision(Drawable* it)
    {
        return ( (r+it->r)<(sqrt(  pow(x-it->x,2) +  pow(y-it->y,2) ) ) );
    }
    virtual bool inside(Drawable* it) ///it inside me
    {
        if(r>=it->r)
            return false;
        else
            return (sqrt(  pow(x-it->x,2) +  pow(y-it->y,2) ) + it->r <= r);
}
    virtual void Draw()=0;

    virtual void InteractionWith(Drawable& it)=0;



    friend class PickUp;
    friend class Player;

};

class PickUp : public Drawable
{
    //int point
    unsigned char type;

public :
    PickUp(float pos_x,float pos_y,int32_t size,unsigned char flag):Drawable(pos_x,pos_y,size),type(flag) {}


    void InteractionWith(Drawable& it);
    void Draw() {};

};


class Player : Drawable
{
    unsigned char pickup;
public :
    Player(float pos_x,float pos_y,int32_t size,unsigned char pickup_):Drawable(pos_x,pos_y,size),pickup(pickup_) {}



    void InteractionWith(Drawable& it);
    void Draw() {};
};


#endif // DRAWABLE_H_INCLUDED