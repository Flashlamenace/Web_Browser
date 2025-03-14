#pragma once

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
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
        int         port;

    public:   
        //Getter :
        std::string get_protocol() const;
        std::string get_host    () const;
        
        //setter :
        int set_port            (int port1);
        std::string set_protocol(std::string proto1); 
        std::string set_host    (std::string host1);  
        
        //determine the protocol to use.
        void what_is_port_proto();
        void parse_url(std::string& url); 
};


//Socket Related

class SOCKET : public URL{
   
    private:
        int socket_fd;
        
    public:
        int connect_to_server();        
        void send_request(char *request_msg);
        std::string receive_request(char *buffer, size_t buffer_size);
};
