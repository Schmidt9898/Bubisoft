#ifndef BUBI_PACKAGE_H_INCLUDED
#define BUBI_PACKAGE_H_INCLUDED

#include <vector>
#include <memory.h>
#include <iostream>
#include <string>

struct Bubi_package
{
    char flag=0;///if átfedést lehetővé teszi
    char pickup_flag=0;/// 2*1 byte but actually 4 byte
    float pos_x=0,    /// 4 byte
          pos_y=0;    /// 4 byte
    float mom_x=0,    /// 4 byte
          mom_y=0;    /// 4 byte
    int32_t p_size=0; /// 4 byte
    uint32_t p_id=0;/// 4 byte
//char pickup_flag; ///1 byte but 4 byte

    Bubi_package(char _flag,char _pickup_flag,///TODO bool[]
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
        std::string value="";
        std::cout<<pos_x<<std::endl;
        value+=std::to_string(flag);
        value+=" : ";
        value+=std::to_string(pickup_flag);
        value+=" : ";
        value+=std::to_string(pos_x);
        value+=" : ";
        value+=std::to_string(pos_y);
        value+=" : ";
        value+=std::to_string(mom_x);
        value+=" : ";
        value+=std::to_string(mom_y);
        value+=" : ";
        value+=std::to_string(p_size);
        value+=" : ";
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

struct Bubi_Factory
{
public :
    int Make_buffer_from_vector(std::vector<Bubi_package> * vec,char *buff)
    {
        std::cout<<vec->size();

        uint16_t size_of_buffer = vec->size();// * sizeof(Bubi_package);

        memcpy(buff, &vec[0] , size_of_buffer);

        return size_of_buffer;
    }

    std::vector<Bubi_package> * Make_vector_from_buffer(char* buff,int b_size)
    {
        uint16_t p_size=b_size/sizeof(Bubi_package);
        Bubi_package p[p_size];

        memcpy(p,buff, b_size);
        std::vector<Bubi_package> *vec = new std::vector<Bubi_package>(p,p+p_size);

        delete buff;
        return vec;
    }

};
#endif // BUBI_PACKAGE_H_INCLUDED
