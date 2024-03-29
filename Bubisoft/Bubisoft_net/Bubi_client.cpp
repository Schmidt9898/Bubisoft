#include "Bubi_client.h"



Bubi_Client::Bubi_Client()
{
std::cout<<"ne hasznalj meg."<<std::endl;
}

Bubi_Client::~Bubi_Client()
{
    run=false;
    SDLNet_TCP_Close(tcp_socket);

    sender->join();
    receiver->join();
    searcher->join();
}

Bubi_Client::Bubi_Client(const char * _ip,int _port)
{
    int code;
    code=SDLNet_ResolveHost(&tcp_ip,_ip,_port);
    if(code!=0)
    {

        throw new Cant_cast_ip_exception(SDLNet_GetError());
    }

};

Bubi_Client::Bubi_Client(const char * _ip,int _port,size_t burst_size)
{
    package_size=burst_size;
    int code;
    code=SDLNet_ResolveHost(&tcp_ip,_ip,_port);
    if(code!=0)
    {
        throw new Cant_cast_ip_exception(SDLNet_GetError());
    }

};





void Bubi_Client::Start_matchmaking()
{
    ///broadcast for server ip...
    //TODO
   // int code;
  //  code=SDLNet_ResolveHost(&tcp_ip,"localhost",12345);
    ///connect to server...
    tcp_socket=SDLNet_TCP_Open(&tcp_ip);

    if(!tcp_socket)/// socket null
    {
        connected=false;
        throw new Cant_connect_exception(SDLNet_GetError());



    }
    connected=true;

    ///get unique id from con server port
    IPaddress *remote_ip;

    remote_ip=SDLNet_TCP_GetPeerAddress(tcp_socket);
    Bubi_ID=(uint32_t)remote_ip->port;
    std::cout<<" port"<<Bubi_ID <<std::endl;


    ///start 2 thread writing and reading

    sender = new std::thread(Bubi_Client::Sender_loop,this);
    receiver = new std::thread(Bubi_Client::Reader_loop,this);

}

void Bubi_Client::Sender_loop()
{

    while(connected && run)
    {
        std::unique_lock<std::mutex> key(OUT_buff_M);///lock
        while(OUT_buffer.size()>0)
        {

            ///char* buff_to_send= new char[OUT_buffer[0]->size()*sizeof(Bubi_package)];  ezt valami elképesztően fáradtan írtam


            char* buff_to_send = (char*) &(*(OUT_buffer[0]))[0];
            size_t buff_size=OUT_buffer[0]->size()*sizeof(Bubi_package);



            ///factory.Make_buffer_from_vector(OUT_buffer[0],buff_to_send);

            int error=SDLNet_TCP_Send(tcp_socket,buff_to_send,buff_size);

            ///delete temp buff
            OUT_buffer.erase(OUT_buffer.begin());
            delete buff_to_send;



            if(error<buff_size)
            {
                key.unlock();

                //throw new Lost_connection_exception(SDLNet_GetError());
            }
        }

        OUT_buff_C.wait(key);
        key.unlock();///gondold át még egyszer.
    }

}
/*
void Bubi_Client::Send_package(Bubi_package * tomb,unsigned int size_)
{
///javít maybe

    char* buff_to_send= new char[size_*sizeof(Bubi_package)];
    memcpy(buff_to_send, tomb, size_);


    OUT_buff_M.lock();
    int error=SDLNet_TCP_Send(tcp_socket,buff_to_send,size_);

    OUT_buff_M.unlock();


    if(error<(int)size_)
    {
        //throw new Lost_connection_exception(SDLNet_GetError());
         std::cout<<"hiba a client sockettel iras"<<std::endl;
    }

    delete tomb;
    delete buff_to_send;

}*/

void Bubi_Client::Reader_loop()
{
    int32_t bytesize=0;
    char * buff=nullptr;
    while(connected && run)
    {
        buff= (char*) malloc(package_size);

        bytesize = SDLNet_TCP_Recv(tcp_socket,buff,package_size);


        if(bytesize<0)
        {
//            throw new Lost_connection_exception(SDLNet_GetError());

            connected=false;
            break;
        }

        std::vector<Bubi_package> *vec=factory.Make_vector_from_buffer(buff,bytesize);

        delete buff;

        IN_buff_M.lock();

        IN_buffer.push_back(vec);
        ///notify
        IN_buff_C.notify_all();
        IN_buff_M.unlock();


    }
    if(buff!=nullptr)
    {
        delete buff;///maybe
    }
std::cout<<"client olvaso hiba"<<std::endl;

}

void Bubi_Client::Push_Bubivector(std::vector<Bubi_package> *vec)
{

     std::cout<<"client pushed"<<std::endl;
    OUT_buff_M.lock();
    OUT_buffer.push_back(vec);
    /// notify
    OUT_buff_C.notify_all();

    OUT_buff_M.unlock();

}

std::vector<Bubi_package>* Bubi_Client::Pop_Bubivector()
{

    std::vector<Bubi_package> *retu= new std::vector<Bubi_package>() ;

    std::unique_lock<std::mutex> key(IN_buff_M);///lock
    while(true)
    {
        if(IN_buffer.size()>0)
        {

            for(unsigned int i=0; i<IN_buffer.size(); i++)
            {
                retu->insert(retu->end(),IN_buffer[i]->begin(),IN_buffer[i]->end());
            }
            IN_buffer.clear();
            break;

        }
        else
        {

            ///nincs benne semmi, akkor várunk
            ///wait for package
            IN_buff_C.wait(key);
            /// megint lock
            //return nullptr;
        }

    }
    key.unlock();

    return retu;



}

uint32_t Bubi_Client::Get_ID(){
return Bubi_ID;
}
bool Bubi_Client::IsConected()
{
    return connected;
}

void Bubi_Client::Close_Client(){
run=false;
}

void Bubi_Client::Set_burst_size(size_t size){
package_size=size;
}

void Bubi_Client::setIPort(const char* _ip,int _port)
{
    int code;
    code=SDLNet_ResolveHost(&tcp_ip,_ip,_port);
    if(code!=0)
    {

        //throw new Cant_cast_ip_exception(SDLNet_GetError());
        std::cout<<"wrong ip"<<std::endl;
    }

}



