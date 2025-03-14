#include "../includes/network.hpp"

//                           IN URL :
        //Getter :
std::string URL::get_protocol() const {return protocol;}
std::string URL::get_host    () const {return host;}
        
        //setter :
int URL::set_port            (int port1)          {return port = port1;}
std::string URL::set_protocol(std::string proto1) {return protocol = proto1;}
std::string URL::set_host    (std::string host1)  {return host = host1;}

        //determine the protocol to use.
void URL::what_is_port_proto(){
    const std::string& protocol = get_protocol();

        if (protocol == "http") {
            set_port(80);
            }
        else {
            set_port(443);
        }
}
//Peut être réimplémenter ça en utilisant les stringstream ? plus lisible ?
void URL::parse_url(std::string& url){
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

//                  IN SOCKET
int SOCKET::connect_to_server(){
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

    std::cout << "Connected to " << host << " on port " << port << std::endl << std::endl;

    freeaddrinfo(res);
           
    return socket_fd;
}
        
        
void SOCKET::send_request(char *request_msg){
        
    send(socket_fd, request_msg, strlen(request_msg), 0); 
        
}

std::string SOCKET::receive_request(char *buffer, size_t buffer_size){    
            
    int sizeof_msg_received = 0;
    std::string response ="";

    while( ( sizeof_msg_received = recv(socket_fd, buffer, buffer_size, 0)) > 0){

        buffer[sizeof_msg_received] = '\0'; // Null-terminate the received data

        response.append(buffer);
    }
return response;
}



