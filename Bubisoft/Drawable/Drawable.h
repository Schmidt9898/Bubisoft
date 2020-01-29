#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED
#include <cmath>
class Drawable
{
protected:
    const uint32_t id;
    float x, y, r;
    uint32_t p;
public:
    Drawable(uint32_t id_,float pos_x,float pos_y,float size,int32_t point):id(id_),x(pos_x),y(pos_y),r(size),p(point) {};


    virtual ~Drawable() {};

    virtual bool collision(Drawable* it)
    {
        return ( (r+it->r)<(sqrt(  pow(x-it->x,2) +  pow(y-it->y,2) ) ) );
    }
    virtual bool inside(Drawable* it) ///me inside it
    {
        //std::cout << "inside test" << std::endl;
        if(r>=it->r)
            return false;
        else
            return ((sqrt(  pow(x-it->x,2) +  pow(y-it->y,2) ) + r )<= it->r);
    }

    virtual void Draw()=0;

    virtual void InteractionWith(Drawable& it)=0;

    float get_x() {return x;}
    float get_y() {return y;}
    float get_r() {return r;}
    uint32_t get_id() {return id;}
    void set_r(float rr) {r=rr;}
    uint32_t getPoint() {return p;}
    void setPoint(uint32_t pp) {p=pp;}
    void addPoint(uint32_t pp) {p+=pp;}

   /* uint32_t get_id(){return id;}
    int32_t get_point(){return p;}
    float get_x(){return x;}
    float get_y(){return y;}
    float get_r(){return r;}


    void set_point(int32_t pont){p=pont;}
    void set_x(float x_){x=x_;}
    void set_y(float y_){y=y_;}
    void set_r(float r_){r=r_;}
    */




    friend class PickUp;
    friend class Player;
    friend class Client;

};

class PickUp : public Drawable
{
    //int point
    unsigned char type;

    std::chrono::system_clock::duration length = std::chrono::system_clock::duration::zero();

public :
    PickUp(uint32_t id_,float pos_x,float pos_y,float size,unsigned char flag,int32_t point):Drawable(id_,pos_x,pos_y,size,point),type(flag) {};

    void InteractionWith(Drawable& it){};
    void Draw() {};
    std::chrono::system_clock::duration getLength() {
        return length;
    }
uint32_t playerakimegevett=-1;
    unsigned char get_type() {return type;}
    void set_type(unsigned char t) {type=t;}

};


class Player : public Drawable
{
    unsigned char pickup;
    bool ready;
public :
    Player(uint32_t id_,float pos_x,float pos_y,float size,unsigned char pickup_):Drawable(id_,pos_x,pos_y,size,0),pickup(pickup_) {ready=false;};

    void update(float pos_x_, float pos_y_, float size_, unsigned char pickup_, int32_t point) {
        x=pos_x_;
        y=pos_y_;
        r=size_;
        pickup=pickup_;
        p=point;
    }

    bool isReady() {return ready;}
    void setReady(bool ready_) {ready=ready_;}

    void InteractionWith(Drawable& it){};
    void Draw() {};

};

class Client : public Drawable
{
    float mom_x,mom_y;
    unsigned char pickup;
    bool ready;
    float max_x=10;
    float max_y=10;
    float min_x=-10;
    float min_y=-10;
    std::string name;
    std::chrono::system_clock::time_point last_update = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point pickup_get_time;
    //std::chrono::system_clock::duration pickup_length = std::chrono::system_clock::duration:: ;

public:
    Client(uint32_t id_,float pos_x,float pos_y,unsigned char pickup_,float mom_x_, float mom_y_):Drawable(id_,pos_x,pos_y,0.06,0),mom_x(mom_x_),mom_y(mom_y_),pickup(pickup_) {ready=false;}

    void InteractionWith(Drawable& it) {};
    void Draw() {};

    bool isReady() {return ready;}
    void setReady() {ready=true; pickup=Flag::notset;}

    void update() {
        last_update = std::chrono::system_clock::now();
    }
    std::chrono::system_clock::time_point getLastUpdate() {
        return last_update;
    }

    /*void set_pickup_get_time() {
        pickup_get_time = std::chrono::system_clock::now();
    }

    void set_pickup_duration(std::chrono::system_clock::duration dur) {
     //   pickup_length=dur;
    }*/
 unsigned char get_pickup() {return pickup;}
    void set_pickup(unsigned char c) {pickup=c;}

    void update_Move(float mom_x_, float mom_y_) {
        mom_x+=mom_x_;
        mom_y+=mom_y_;
        if(mom_x>2)
            mom_x=2;
        if(mom_y>2)
            mom_y=2;


        if(mom_x_==0 && mom_y_==0){
        mom_x/=1.05;
        mom_y/=1.05;
        }
        /*x+=mom_x;
        y+=mom_y;

        if(mom_x_==0 && mom_y_==0){
        mom_x/=1.05;
        mom_y/=1.05;
        }



        if(sqrt(x*x+y*y)+r >= 10)
        {
            mom_x/=1.05;
            mom_y/=1.05;

            /*float s=sqrt(x*x+y*y)*10;
            x -= x/s;
            y -= y/s;*/
        }
    void Move_one() {
        x+=mom_x;
        y+=mom_y;




        if(sqrt(x*x+y*y)+r >= 10)
        {
            mom_x/=1.05;
            mom_y/=1.05;
            float s=sqrt(x*x+y*y)*100;
            mom_x+=-x/s;
            mom_y+=-y/s;
            /*float s=sqrt(x*x+y*y)*10;
            x -= x/s;
            y -= y/s;*/
        }
/*
        if(pickup=='c' || pickup=='d' || pickup=='e' || pickup=='f') {
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> diff = end-pickup_get_time;
            if(diff>pickup_length) {
                pickup = '0';
            }
        }*/
    }

    void Move() {
        x+=mom_x;
        y+=mom_y;
        if(sqrt(x*x+y*y)+r >= 10)
        {
            mom_x=0;
            mom_y=0;

            float s=sqrt(x*x+y*y)*10;
            x -= x/s;
            y -= y/s;
        }
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

    float getMin_x() {
        return min_x;
    }

    float getMin_y() {
        return min_y;
    }

    float getMax_x() {
        return max_x;
    }

    float getMax_y() {
        return max_y;
    }

    void setPosition(float x_, float y_) {
        x=x_;
        y=y_;
    }
};

#endif // DRAWABLE_H_INCLUDED
