#include "Bubi_server.h"

 Bubi_Server::~Bubi_Server(){
    ///Legyen vége a szálaknak.
    sender->join();
    receiver->join();
    Accepter->join();
    Broadcaster->join();
///TODO bővíteni
    }

Bubi_Server::Bubi_Server(int tcp_port,int udp_port)
    {

        SDLNet_ResolveHost(&tcp_ip,NULL,tcp_port);
        SDLNet_ResolveHost(&udp_ip,NULL,udp_port);

    }

bool Bubi_Server::Open_Server(){
    tcp_server=SDLNet_TCP_Open(&tcp_ip);

    if(!tcp_server){
        return false;
    }
/* not ready
    udp_server=SDLNet_UDP_Open(11111);

    if(!udp_server){
        return false;
    }
Broadcaster= new std::thread(Bubi_server::Broadcasting_loop,this);

*/

Accepter =  new std::thread(Bubi_Server::Accepting_TCP_loop,this);

sender= new std::thread(Bubi_Server::Sender_loop,this);
receiver=new std::thread(Bubi_Server::Reader_loop,this);


 return true;
}

 void Bubi_Server::Accepting_TCP_loop()
{
TCPsocket client;

while(true){

    client = SDLNet_TCP_Accept(tcp_server);
    if(!client)
    {
        //levéd
        clients.push_back(client);
        client=NULL;
        //felold

    }
    else
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }



}


}


void Bubi_Server::Send_package(Bubi_package * tomb,unsigned int size_)
{

    char* buff_to_send= new char[size_];
    memcpy(buff_to_send, tomb, size_);
    OUT_buff_M.lock();
    //int error=SDLNet_TCP_Send(tcp_socket,buff_to_send,size_);
    ///todo
    OUT_buff_M.unlock();


/*    if(error<(int)size_)
    {
        throw new Lost_connection_exception(SDLNet_GetError());
    }*/

    delete tomb;
    delete buff_to_send;

}

void Bubi_Server::Reader_loop()
{
    int bytesize=0;
    char * buff=nullptr;
    while(run)
    {
        buff=new char[package_size];
        ///TODO
       /* bytesize = SDLNet_TCP_Recv(tcp_socket,buff,package_size);
        if(bytesize<0)
        {
            throw new Lost_connection_exception(SDLNet_GetError());
        }
        */
        std::vector<Bubi_package> vec=factory.Make_vector_from_buffer(buff,bytesize);
        IN_buff_M.lock();
        IN_buffer.push_back(vec);
        ///notify
        IN_buff_C.notify_all();
        IN_buff_M.unlock();

    }
}


void Bubi_Server::Sender_loop()
{

    while(run)
    {
        std::unique_lock<std::mutex> key(OUT_buff_M);///lock
        while(OUT_buffer.size()>0)
        {
            char* buff_to_send= new char[OUT_buffer[0].size()];
            int buff_size=factory.Make_buffer_from_vector(
                              OUT_buffer[0],buff_to_send);
            ///TODO
           // int error=SDLNet_TCP_Send(tcp_socket,buff_to_send,buff_size);

            ///delete temp buff
            OUT_buffer.erase(OUT_buffer.begin());
            delete buff_to_send;



            /*if(buff_size)
            {
                key.unlock();
                throw new Lost_connection_exception(SDLNet_GetError());
            }*/
        }
        OUT_buff_C.wait(key);
        key.unlock();///gondold át még egyszer.
    }

}

void Bubi_Server::Push_Bubivector(std::vector<Bubi_package> &vec)
{
    OUT_buff_M.lock();
    OUT_buffer.push_back(vec);
    /// notify
    OUT_buff_C.notify_all();

    OUT_buff_M.unlock();

}

std::vector<Bubi_package>* Bubi_Server::Pop_Bubivector()
{
    std::vector<Bubi_package> *retu= new std::vector<Bubi_package>() ;
    std::unique_lock<std::mutex> key(IN_buff_M);///lock
    while(true)
    {
        if(IN_buffer.size()>0)
        {

            for(unsigned int i=0; i<IN_buffer.size(); i++)
            {
                retu->insert(retu->end(),IN_buffer[i].begin(),IN_buffer[i].end());
            }
            IN_buffer.clear();
            break;

        }
        else
        {
            /*
            if(IN_buffer.size()>0)
            {
                retu.insert(retu.end(),IN_buffer[0].begin(),IN_buffer[i].end());

            }
            else{
                    */
            ///nincs benne semmi, akkor várunk
            ///wait for package
            IN_buff_C.wait(key);
            /// megint lock
            //return nullptr;
        }

    }
    key.unlock();
    //IN_buff_M.unlock();
    return retu;



}


