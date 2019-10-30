#include "Bubi_client.h"
/*
Bubi_Client::Bubi_Client(char * _ip,int _port)
    {
        int code;
        code=SDLNet_ResolveHost(&ip,_ip,_port);
        if(code!=0)
        {
            throw new Cant_cast_ip_exception(SDLNet_GetError());
        }
        //delete this;
    };*/



    Bubi_Client::Bubi_Client(TCPsocket & ready_socket)
    {
        tcp_socket = ready_socket;
    }

     Bubi_Client::~Bubi_Client()
    {
        sender->join();
        receiver->join();
        searcher->join();
    }




    Bubi_Client::Bubi_Client(char * _ip,int _port)
    {
        int code;
        code=SDLNet_ResolveHost(&tcp_ip,_ip,_port);
        if(code!=0)
        {
            ///TODO cleanup
            throw new Cant_cast_ip_exception(SDLNet_GetError());
        }

    };

    void Bubi_Client::Start_matchmaking() throw (Cant_cast_ip_exception)
    {
        ///broadcast for server ip...
        //TODO
        int code;
        code=SDLNet_ResolveHost(&tcp_ip,"localhost",12345);
        ///connect to server...
        tcp_socket=SDLNet_TCP_Open(&tcp_ip);
        //for(int i = 0;i<5;i++) // késöbbre
        if(!tcp_socket)/// socket null
        {
            throw new Cant_connect_exception(SDLNet_GetError());
        }
        connected=true;

        ///get and set my unique id for the thread
        /*
        char id_data[4];
        int data_size;
        do{
            data_size+=SDLNet_TCP_Recv(tcp_socket,&id_data,4);
        }
        while(data_size<4);

        std::memcpy(&Bubi_ID, id_data, 4);
*/
        ///start 2 thread writing and reading

        sender = new std::thread(Bubi_Client::Send_Buffer,this);
        receiver = new std::thread(Bubi_Client::Read_Buffer,this);



        /// exception handeling  //sory whaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaat?
    }

     void Bubi_Client::Send_Buffer(){
         while(connected){
     OUT_buff_M.lock();
     if(OUT_buffer.size()>0){
     char* buff_to_send= new char[OUT_buffer[0].size()];
     int buff_size=factory.Make_buffer_from_vector(
               OUT_buffer[0],buff_to_send);
                OUT_buffer[0].erase(OUT_buffer[0].begin());
                int error=SDLNet_TCP_Send(tcp_socket,buff_to_send,buff_size);
        if(error<buff_size){
            throw new Lost_connection_exception(SDLNet_GetError());
        }
     }else{
         /// TODO wait
     }


     OUT_buff_M.unlock();
         }
     }
    void Bubi_Client::Read_Buffer(){
        int bytesize=0;
    char * buff=nullptr;
    while(connected){
            buff=new char[package_size];
    bytesize = SDLNet_TCP_Recv(tcp_socket,buff,package_size);
            if(bytesize<0){
                throw new Lost_connection_exception(SDLNet_GetError());
            }
           std::vector<Bubi_package> vec=factory.Make_vector_from_buffer(buff,bytesize);
    IN_buff_M.lock();
    IN_buffer.push_back(vec);
    ///TODO notify
    IN_buff_M.unlock();

    }


    }



    void Bubi_Client::Push_Bubivector(std::vector<Bubi_package> &vec){
    OUT_buff_M.lock();
    OUT_buffer.push_back(vec);
    ///TODO notify

    OUT_buff_M.unlock();

    }

    std::vector<Bubi_package>* Bubi_Client::Pop_Bubivector(){
    IN_buff_M.lock();
    if(IN_buffer.size()>1)
    {
        std::vector<Bubi_package> retu;
        for(int i=0;i<IN_buffer.size();i++){
            retu.insert(retu.end(),IN_buffer[i].begin(),IN_buffer[i].end());
        }
        return &retu;
    }
    else
    {
        if(IN_buffer.size()>0){
            return &IN_buffer[0];
        }
        else
            return nullptr;
    }


    ///TODO notify
    IN_buff_M.unlock();

    }





