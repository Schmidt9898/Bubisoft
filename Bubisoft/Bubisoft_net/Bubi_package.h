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
    unsigned char space=255;
    unsigned char space0=255;
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
        std::string value="";
        //std::cout<<pos_x<<std::endl;
        value+=flag;
        value+=" : ";
        value+=pickup_flag;
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

    size_t to_buffer_from_array(char *buff,Bubi_package* array,size_t size){

        size_t size_of_buffer = size*sizeof(Bubi_package);



        memcpy(buff,array, size_of_buffer);


        std::cout<<"buff make::"<<std::endl;
        for(int i=0;i<size_of_buffer;i++){
        std::printf("%02x ", buff[i]);
        }
        std::cout<<std::endl;

        return size_of_buffer;
        };


    size_t to_array_from_buffer(Bubi_package* array,char* buff,size_t size){



   /*   std::cout<<"masik::"<<std::endl;
        for(int i=0;i<size;i++){
        std::printf("%02x ", buff[i]);
        }
        std::cout<<std::endl;*/

        size_t a_size=size/sizeof(Bubi_package);
       // Bubi_package* p = new Bubi_package[a_size];
        //std::cout<<"p:"<<p<<" size:"<<p_size<<std::endl;

        memcpy(array,buff, size);
        //std::vector<Bubi_package> *vec = new std::vector<Bubi_package>(p,p+p_size);

        /*std::cout<<"make::"<<std::endl;
          for(int i=0;i<b_size;i++){
        std::printf("%02x ", buff[i]);
        }
        */

        //delete buff;
        return a_size;


    };




    //int Make_buffer_from_vector(std::vector<Bubi_package> * vec,char *buff)
    ///{///hibás ne használd soha   ez jobb tomb=(char*)&vec[0];
/*        //std::cout<<vec->size();

        uint16_t size_of_buffer = vec->size()*sizeof(Bubi_package);// * sizeof(Bubi_package);

        memcpy(buff, &vec[0] , size_of_buffer);
 /*std::cout<<"buff make::"<<std::endl;
        for(int i=0;i<size_of_buffer;i++){
        std::printf("%02x ", buff[i]);
        }*/
/*
        return size_of_buffer;*/
   /// }

    std::vector<Bubi_package> * Make_vector_from_buffer(char* buff,int b_size)
    {

      /*  std::cout<<std::endl;
   for(int i=0;i<28;i++){
        std::printf("%02x ", buff[i]);
        }*/
        //std::cout<<"az:"<<std::string(buff)<<"::"<<std::endl;
        //std::cout<<"buff:"<<buff<<" size:"<<b_size<<std::endl;

      // Bubi_package* p=(Bubi_package*)buff;

if(b_size==-1)
{
    std::cout<<"a kurva éleetbe"<<std::endl;
    return new std::vector<Bubi_package>();

}


        size_t p_size=b_size/sizeof(Bubi_package);
       //Bubi_package* p = new Bubi_package[p_size];
        Bubi_package* p = (Bubi_package*)malloc(p_size);
     // std::cout<<"p :  "<<p<<" buff:"<<buff<<std::endl;
       // std::cout<<"p [0] hibásnak kell lennie|| "<<p[0].ToString()<<" size:"<<p_size<<std::endl;

        memcpy(p,buff, b_size);
        std::vector<Bubi_package> *vec = new std::vector<Bubi_package>(p,p+p_size);

        /*vec->resize(p_size);

        for(unsigned int i=0;i<p_size;i++){

            (*vec)[i]=p[i];
        }*/


       // std::cout<<"vector vissza|| "<<(*vec)[0].ToString()<<std::endl;
        //std::cout<<"make::"<<std::endl;
        /*  for(int i=0;i<b_size;i++){
        std::printf("%02x ", buff[i]);
        }*/




        //delete buff;
        return vec;
    }

};
#endif // BUBI_PACKAGE_H_INCLUDED
