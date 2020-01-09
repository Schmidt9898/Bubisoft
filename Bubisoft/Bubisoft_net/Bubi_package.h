#ifndef BUBI_PACKAGE_H_INCLUDED
#define BUBI_PACKAGE_H_INCLUDED

#include <vector>
#include <memory.h>
#include <iostream>
#include <string>

struct Bubi_package
{

    ///pls don't change
    unsigned char flag='a';///if átfedést lehetővé teszi
    unsigned char pickup_flag='b';/// 4*1 byte but actually 4 byte
    unsigned char doflag=255;
    unsigned char bringflag=255;
    float pos_x=0,    /// 4 byte
          pos_y=0;    /// 4 byte
    float mom_x=0,    /// 4 byte
          mom_y=0;    /// 4 byte
    float p_size=0; /// 4 byte
    uint32_t p_id=0;/// 4 byte
    uint32_t point=0;///4 byte
//char pickup_flag; ///1 byte but 4 byte

    Bubi_package(unsigned char _flag,unsigned char _pickup_flag,///TODO bool[]
                 float _pos_x,
                 float _pos_y,
                 float _mom_x,
                 float _mom_y,
                 int32_t _p_size,
                 uint32_t _p_id

                ):flag(_flag),pos_x(_pos_x),pos_y(_pos_y),
        mom_x(_mom_x),mom_y(_mom_y),
        p_size(_p_size),p_id(_p_id),pickup_flag(_pickup_flag) {}

    Bubi_package() {};

    std::string ToString()
    {
        std::string value="flag: ";
        //std::cout<<pos_x<<std::endl;
        value+=flag;
        value+=" |  pickup_flag: ";
        value+=pickup_flag;
        value+=" | pos_x: ";
        value+=std::to_string(pos_x);
        value+=" | pos_x: ";
        value+=std::to_string(pos_y);
        value+=" | mom_x: ";
        value+=std::to_string(mom_x);
        value+=" | mom_y: ";
        value+=std::to_string(mom_y);
        value+=" | p_size: ";
        value+=std::to_string(p_size);
        value+=" | p_id: ";
        value+=std::to_string(p_id);
        //  std::cout<<value<<std::endl;
        return value;

    }

};
struct Bubi_name_package
{
    char flag=0;
    char name[23]= {' '};
    uint32_t p_id=0;

    Bubi_name_package(char _flag,uint32_t _p_id,std::string _name)
        :flag(_flag),p_id(_p_id)
    {
        if(_name.size()<23)
            memcpy(name, &_name, _name.size());
        else
            memcpy(name, &_name, 23);
    }
};
/*
enum Flag :char
{
    notset=0,
    player=1,
    pickup=2,
    name=3,
    ready=4,
    not_ready=5
};
*/
enum Flag :char
{
    notset=0,   ///általános player csomag
    player=1,   ///new player
    pickup=2,   ///pickup típusú csomag
    name=3,     ///new name
    ready=4,    ///player készen áll a játékra
    not_ready=5,///player nem áll készen a játékra
    dead=6,     ///player meghalt
    disconn=7,  ///player lecsatlakozott
    replay=8,   ///player újra játszani akar
    winner=9,   ///playernek van a legtöbb pontja
    game_end=10,
    dead_flag=20,

    food=11,
    food1=12,
    immortal=13,
    doublepoint=14
};

enum purpose :char
{
    none=0,
    add=1,
    delet=2,
    update=3,
    get_stat=4,
    get_name=5,
    set_name=6,
    stat=7,
    get_tree=8
};



struct Bubi_Factory
{
public :
///kiolvassa a stringet ha ez tényleg egy név package
    std::string get_name(Bubi_package &p)
    {
        if(p.flag==Flag::name)
            return "not a name";
size_t meret=sizeof(Bubi_package)-5;
        char name[meret];
        //char * cp = (char*)&p;
        memcpy(name,&p+1,meret);
        return std::string(name);
    }
    ///bármien package-bő név packaget csinál
    void set_name(Bubi_package &p,std::string name)
    {

        p.flag=Flag::name;
size_t meret=sizeof(Bubi_package)-5;
        memcpy(&p+1,name.c_str(),meret);



    }

    std::vector<Bubi_package> * Make_vector_from_buffer(char* buff,int b_size)
    {


        if(b_size<=0)
        {
            std::cout<<"uresseg"<<std::endl;
            return new std::vector<Bubi_package>();

        }


        size_t p_size=b_size/sizeof(Bubi_package);

        std::vector<Bubi_package> *vec = new std::vector<Bubi_package>();
        vec->resize(p_size);

        memcpy(vec->data(),buff, b_size);

        return vec;
    }

};
#endif // BUBI_PACKAGE_H_INCLUDED
