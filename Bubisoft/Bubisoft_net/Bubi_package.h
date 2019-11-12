#ifndef BUBI_PACKAGE_H_INCLUDED
#define BUBI_PACKAGE_H_INCLUDED

#include <vector>
#include <memory.h>
#include <iostream>
#include <string>

struct Bubi_package
{
    unsigned char flag='a';///if átfedést lehetővé teszi
    unsigned char pickup_flag='b';/// 2*1 byte but actually 4 byte
    unsigned char space0=255;
    unsigned char space1=255;
    float pos_x=4,    /// 4 byte
          pos_y=4;    /// 4 byte
    float mom_x=4,    /// 4 byte
          mom_y=0;    /// 4 byte
    int32_t p_size=0; /// 4 byte
    uint32_t p_id=0;/// 4 byte
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


///std::memcpy(hova, honnan, mennyit);
///A vector array byte jai lemásolódnak egy ugyan akkora méretû bufferba amit
///elõre kell megadni és allocálni
///vectort referencia szerint kell megadni

enum Flag :char
{
    notset=0,
    player=1,
    pickup=2,
    name=3
};




struct Bubi_Factory
{
public :

    std::string get_name(Bubi_package &p)
    {
        if(p.flag=Flag::name)
            return "not a name";

        char name[23];
        //char * cp = (char*)&p;
        memcpy(name,&p+1,23);
        return std::string(name);
    }
    void set_name(Bubi_package &p,std::string name)
    {

        p.flag=Flag::name;

        memcpy(&p+1,name.c_str(),23);



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
