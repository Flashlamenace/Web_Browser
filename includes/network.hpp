#pragma once

#include <cstddef>
#include <iostream>
#include <unistd.h>
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
        //Constructor :
        URL(const std::string& protocol, std::string& host) : protocol(protocol), host(host) {}
        
        //Getter :
        std::string get_protocol() const {return protocol;}
        std::string get_host    () const {return host;}
        
        //setter :
        int set_port (int port1){return port = port1;} 

        static URL parse_url(std::string& url){
            size_t      position_protocol = url.find("://");
            size_t      position_port     = url.find(":", position_protocol);
            std::string protocol = url.substr(0, position_protocol);
            std::string host     = url.substr(position_protocol + 3, position_port);

            return URL(protocol, host);
        }    

};

class PROTOCOL : URL{
    //Prendre en compte tout le reste...

    public:
        void what_is_port_proto(){
            std::string protocol = get_protocol();

                if (protocol == "http") {
                    set_port(80);
                }
                else {
                    set_port(443);
                }

        }
};

//Socket Related

class SOCKET : URL{
    private:
        int socket_fd;
    public:
        bool connect_to_server(){
            socket_fd = socket(AF_INET, SOCK_STREAM, 0);
            
            if (socket_fd < 0) {std::cerr << "Problem while creating socket. \n";}

            struct sockaddr_in server_addr;
            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons(port);
            inet_pton(AF_INET, host.c_str(), &server_addr.sin_addr);
    
            if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
                std::cerr << "Connection failed\n";
                close(socket_fd);
                return false;
            }
            return true;
        }

};