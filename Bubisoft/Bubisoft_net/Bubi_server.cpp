#include "Bubi_server.h"

 Bubi_Server::~Bubi_Server(){
    ///Legyen vége a szálaknak.
    Sender->join();

    Accepter->join();
    Broadcaster->join();
    for (std::thread* reader : Readers){
        reader->join();
    }
    std::cout<<"server closed"<<std::endl;
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

Sender= new std::thread(Bubi_Server::Sender_loop,this);
//receiver=new std::thread(Bubi_Server::Reader_loop,this);


 return true;
}

 void Bubi_Server::Accepting_TCP_loop()
{
TCPsocket client;

while(true){

    client = SDLNet_TCP_Accept(tcp_server);
    if(client)
    {
        //levéd
        std::cout<<"new client"<<std::endl;
        clients.push_back(&client);
        Readers.push_back(new std::thread(Bubi_Server::Reader_loop,this,&client));

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

     for (TCPsocket* client : clients) {
        int error=SDLNet_TCP_Send(*client,buff_to_send,size_);
    if(error<(int)size_)///nem megfelelő
    { ///TODO hibakezelés
     //   throw new Lost_connection_exception(SDLNet_GetError());
     std::cout<<"hiba a sockettel"<<std::endl;
    }

    }
    //int error=SDLNet_TCP_Send(tcp_socket,buff_to_send,size_);

    OUT_buff_M.unlock();


/*    */

    delete tomb;
    delete buff_to_send;

}

void Bubi_Server::Reader_loop(TCPsocket *client)
{
    std::cout<<"reader started"<<std::endl;
    int bytesize=0;
    char * buff=nullptr;
    while(run)
    {
        //std::cout<<"reader loop"<<std::endl;
        buff=new char[package_size];


        bytesize = SDLNet_TCP_Recv(*client,buff,package_size);
        std::cout<<"csomag erkezett"<<std::endl;
        if(bytesize<0)///nem megfelelő
        {
            ///TODO hibakezelés
            //   throw new Lost_connection_exception(SDLNet_GetError());
            std::cout<<"hiba a sockettel olvasa's"<<std::endl;
            break;
        }

        std::vector<Bubi_package> vec=factory.Make_vector_from_buffer(buff,bytesize);
        std::cout<<"e "<<bytesize<<std::endl;
//std::cout<<"beerkezett toltes"<<std::endl;
        IN_buff_M.lock();
        IN_buffer.push_back(vec);
        ///notify
        IN_buff_C.notify_all();
        IN_buff_M.unlock();
        std::cout<<"server olvasott"<<std::endl;

    }
    clients.remove(client);
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

            for (TCPsocket* client : clients)
            {
                int error=SDLNet_TCP_Send(*client,buff_to_send,buff_size);
                if(error<(int)buff_size)///nem megfelelő
                {
                     ///TODO hibakezelés
                    //   throw new Lost_connection_exception(SDLNet_GetError());
                    std::cout<<"hiba a sockettel 2"<<std::endl;
                }

            }




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
    //std::cout<<retu->size()<<std::endl;
    return retu;



}

void Bubi_Server::Close_Server(){
run=false;
}

