#pragma once

#include <cstddef>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <sys/types.h>
#include <netdb.h>



class URL{

    protected:
        std::string protocol;
        std::string host; 
        std::string path;
        int         port;
        
    public:   
        //Constructor
        URL(std::string &&url); 

        //Getter :
        std::string get_protocol() const;
        std::string get_host    () const;
        
        //setter :
        int set_port            (int port1);
        std::string set_protocol(std::string proto1); 
        std::string set_host    (std::string host1);  
        
        // A mettre ailleurs : 
        void what_is_port_proto();
};


//Socket Related

class SOCKET{
    private:
        int socket_fd;
        
    public:
        //Constructor :
        SOCKET(URL &Url);

        void send_request(char *request_msg);
        std::string receive_request(char *buffer, size_t buffer_size);
};
