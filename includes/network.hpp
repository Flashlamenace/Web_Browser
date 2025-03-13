#pragma once

#include <vector>
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
        //Constructor :
        //URL(const std::string& protocol, std::string& host) : protocol(protocol), host(host) {}
        
        //Getter :
        std::string get_protocol() const {return protocol;}
        std::string get_host    () const {return host;}
        
        //setter :
        int set_port            (int port1)          {return port = port1;}
        std::string set_protocol(std::string proto1) {return protocol = proto1;}
        std::string set_host    (std::string host1)  {return host = host1;}

        //determine the protocol to use.
        void what_is_port_proto(){
            const std::string& protocol = get_protocol();

                if (protocol == "http") {
                    set_port(80);
                }
                else {
                    set_port(443);
                }

        }

        void parse_url(std::string& url){
            size_t      position_protocol = url.find("://");
            //size_t      position_port     = url.find(":", position_protocol);
            std::string protocol = url.substr(0, position_protocol);
            std::string host_and = url.substr(position_protocol + 3);
            size_t      position_host = host_and.find("/");
            std::string host = host_and.substr(0, position_host);
            
            std::cout << "protocol : " << protocol << " Host : " << host << std::endl;
            
            set_host    (host);
            set_protocol(protocol);
        }    

};


//Socket Related

class SOCKET : public URL{
    private:
        int socket_fd;
        
    public:

        int connect_to_server(){
            socket_fd = socket(AF_INET, SOCK_STREAM, 0);
            
            if (socket_fd < 0) {std::cerr << "Problem while creating socket. \n";}

            struct addrinfo hints, *res;
            memset(&hints, 0, sizeof(hints));
            hints.ai_family = AF_INET;      // Only IPv4 addresses
            hints.ai_socktype = SOCK_STREAM;

            std::cout << "host : " << host << " port : " << port << std::endl;
        
            int gai_result = getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &res);
            if (gai_result != 0) {
                std::cerr << "getaddrinfo failed: " << gai_strerror(gai_result) << std::endl;
                close(socket_fd);
                return 0;
            }
            if (connect(socket_fd, res->ai_addr, res->ai_addrlen) < 0) {
                std::cerr << "Connection failed\n";
                close(socket_fd);
                freeaddrinfo(res);  // Clean up
                return 0;
            }

            std::cout << "Connected to " << host << " on port " << port << std::endl;

            freeaddrinfo(res);
           
            return socket_fd;
        }
        
        
        void send_request(char *request_msg){
        
                send(socket_fd, request_msg, strlen(request_msg), 0); 
        
        }

        std::string receive_request(char *buffer, size_t buffer_size){    
        
            int sizeof_msg_received = recv(socket_fd, buffer, buffer_size, 0);

            if (sizeof_msg_received > 0) {
                buffer[sizeof_msg_received] = '\0'; // Null-terminate the received data
            }
        
        return std::string(buffer);
        }
};
