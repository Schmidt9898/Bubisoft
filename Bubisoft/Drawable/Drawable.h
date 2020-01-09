#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED
#include <cmath>
class Drawable
{
protected:
    const uint32_t id;
    float x, y;
    float r;

public:
    Drawable(uint32_t id_,float pos_x,float pos_y,int32_t size):id(id_),x(pos_x),y(pos_y),r(size) {};


    virtual ~Drawable(){};

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


    uint32_t get_id(){return id;}
    float get_x(){return x;}
    float get_y(){return y;}
    float get_r(){return r;}


    //void set_id(uint32_t id_){id=id_;}
    void set_x(float x_){x=x_;}
    void set_y(float y_){y=y_;}
    void set_r(float r_){r=r_;}




    friend class PickUp;
    friend class Player;

};

class PickUp : public Drawable
{
    //int point
    unsigned char type;

public :
    PickUp(uint32_t id_,float pos_x,float pos_y,int32_t size,unsigned char flag):Drawable(id_,pos_x,pos_y,size),type(flag) {};


    void InteractionWith(Drawable& it){};
    void Draw() {};

};


class Player : public Drawable
{
    unsigned char pickup;

public :
    Player(uint32_t id_,float pos_x,float pos_y,int32_t size,unsigned char pickup_):Drawable(id_,pos_x,pos_y,size),pickup(pickup_) {};
int vertex_id=-1;
    void InteractionWith(Drawable& it){};
    void Draw() {};

};


#endif // DRAWABLE_H_INCLUDED
