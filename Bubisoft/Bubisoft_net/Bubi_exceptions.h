#ifndef BUBI_EXCEPTIONS_H_INCLUDED
#define BUBI_EXCEPTIONS_H_INCLUDED


#include <exception>
#include <string>

class Lost_connection_exception : public std::exception
{
   std::string msg_from_IPapi;
    public:
        Lost_connection_exception(std::string msg) : msg_from_IPapi(msg){};
        const char* what() const throw() { return "hiba todo"; }
};
class Cant_cast_ip_exception : public std::exception
{
   std::string msg_from_IPapi;
    public:
        Cant_cast_ip_exception(std::string msg) : msg_from_IPapi(msg){};
        const char* what() const throw() { return "Nem sikerült az ip meghatarozasa."; }
};
class Cant_connect_exception : public std::exception
{
   std::string msg_from_IPapi;
    public:
        Cant_connect_exception(std::string msg) : msg_from_IPapi(msg){};
        const char* what() const throw() { return "Szerver cím megszerezve de nem lehet csatlakozni. "; }
};
class Natasa : public std::exception
{
   std::string msg_from_IPapi;
    public:
        Natasa(std::string msg) : msg_from_IPapi(msg){};
        const char* what() const throw() { return "we handle it by not handling it."; }
};

#endif // BUBI_EXCEPTIONS_H_INCLUDED
