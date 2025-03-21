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
#include <openssl/ssl.h>



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

class SSL_context{
    private:
        SSL_CTX *ctx;
    public:
         SSL_context();
        ~SSL_context();

        SSL_CTX *get_ctx();
};

class _SSL_connect : public SSL_context{
    private:
        SSL *ssl;
    public:
         _SSL_connect(std::string &hostname, int &socket_fd);
        ~_SSL_connect();
        
        void        SSL_send_request    (char *&request_msg);
        std::string SSL_receive_response(char *&buffer);
};

