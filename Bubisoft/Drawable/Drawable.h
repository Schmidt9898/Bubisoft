#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED
#include <cmath>
class Drawable
{
protected:
    const uint32_t id;
    float x, y;
    int32_t r, p;
public:
    Drawable(uint32_t id_,float pos_x,float pos_y,int32_t size,int32_t point):id(id_),x(pos_x),y(pos_y),r(size),p(point) {};

    virtual ~Drawable() {}

    virtual bool collision(Drawable* it)
    {
        return ( (r+it->r)<(sqrt(  pow(x-it->x,2) +  pow(y-it->y,2) ) ) );
    }
    virtual bool inside(Drawable* it) ///me inside it
    {
        if(r>=it->r)
            return false;
        else
            return (sqrt(  pow(x-it->x,2) +  pow(y-it->y,2) ) + it->r <= r);
    }

    virtual void Draw()=0;

    virtual void InteractionWith(Drawable& it)=0;

    float get_x() {return x;}
    float get_y() {return y;}
    int32_t get_r() {return r;}
    uint32_t get_id() {return id;}
    void set_r(int32_t rr) {r=rr;}



    friend class PickUp;
    friend class Player;
    friend class Client;

};

class PickUp : public Drawable
{
    //int point
    unsigned char type;

public :
    PickUp(uint32_t id_,float pos_x,float pos_y,int32_t size,unsigned char flag,int32_t point):Drawable(id_,pos_x,pos_y,size,point),type(flag) {};

    void InteractionWith(Drawable& it){};
    void Draw() {};

};


class Player : public Drawable
{
    unsigned char pickup;
public :
    Player(uint32_t id_,float pos_x,float pos_y,int32_t size,unsigned char pickup_):Drawable(id_,pos_x,pos_y,size,0),pickup(pickup_) {};

    void InteractionWith(Drawable& it){};
    void Draw() {};

};

class Client : public Drawable
{
    float mom_x,mom_y;
    unsigned char pickup;
    bool ready;
    float max_x=1000;
    float max_y=1000;
    std::string name;
    std::chrono::system_clock::time_point last_update = std::chrono::system_clock::now();

public:
    Client(uint32_t id_,float pos_x,float pos_y,int32_t size,unsigned char pickup_,float mom_x_, float mom_y_):Drawable(id_,pos_x,pos_y,size,0),mom_x(mom_x_),mom_y(mom_y_),pickup(pickup_) {ready=false;}

    void InteractionWith(Drawable& it) {};
    void Draw() {};

    bool isReady() {return ready;}
    void setReady() {ready=true;}

    void update() {last_update = std::chrono::system_clock::now();}
    std::chrono::system_clock::time_point getLastUpdate() {
        return last_update;
    }


    char get_pickup() {return pickup;}

    void Move(float mom_x_, float mom_y_) {
        mom_x=mom_x_;
        mom_y=mom_y_;
        x+=mom_x;
        y+=mom_y;
        if(x<0) x=0;
        if(y<0) y=0;
        if(x>max_x) x=max_x;
        if(y>max_y) y=max_y;
    }

    void setName(std::string p_name) {
        name=p_name;
    }

    void set_flag(unsigned char p_up) {
        pickup=p_up;
    }

    std::string getName() {
        return name;
    }
};

#endif // DRAWABLE_H_INCLUDED
