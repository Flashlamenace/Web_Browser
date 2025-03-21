#include "../includes/network.hpp"

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>


//                           IN URL :
std::string URL::get_protocol() const {return protocol;}
std::string URL::get_host    () const {return host;}
        
int URL::set_port            (int port1)          {return port = port1;}
std::string URL::set_protocol(std::string proto1) {return protocol = proto1;}
std::string URL::set_host    (std::string host1)  {return host = host1;}

void URL::what_is_port_proto(){
    const std::string& protocol = get_protocol();

    if (protocol == "http"){
        set_port(80);
    }
    else{
        set_port(443);
    }
}

URL::URL(std::string &&url){
    std::stringstream url_ss(url);

    std::getline(url_ss, protocol, ':');
    
    if (url_ss.peek() == '/'){
        url_ss.ignore(2);
    }

    std::getline(url_ss, host, '/');
    std::getline(url_ss, path);
}    





//                  IN SOCKET

SOCKET::SOCKET(URL &Url){
    
    std::string port = Url.get_protocol();
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP

    if (getaddrinfo(Url.get_host().c_str(), port.c_str(), &hints, &res) != 0) {
        std::cerr << "getaddrinfo failed: " << gai_strerror(errno) << std::endl; 
    }

    socket_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
   
    if (socket_fd == -1) {
        std::cerr << "Could not create socket" << std::endl;
        freeaddrinfo(res);
    }

     
     if (connect(socket_fd, res->ai_addr, res->ai_addrlen) < 0) {
        std::cerr << "Connection failed" << std::endl;
        close(socket_fd);
        freeaddrinfo(res);
     }

     std::cout << "Connected to server at " << Url.get_host() << ":" << port << std::endl;
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

//          In _SSL :
    
SSL_context::SSL_context(){
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());

    if (!ctx) {
        fprintf(stderr, "SSL_CTX_new() failed.\n");
    }
}

SSL_context::~SSL_context(){
    SSL_CTX_free(ctx);
}

SSL_CTX *SSL_context::get_ctx(){return ctx;}


//TO_DO : Vérifier l'authenticité du certificat du serveur !
_SSL_connect::_SSL_connect(std::string &hostname, int &socket_fd) : SSL_context(){
    ssl = SSL_new(get_ctx());

    if(!SSL_set_tlsext_host_name(ssl, hostname.c_str())){
        fprintf(stderr, "SSL_set_tlsext_host_name() failed.\n");
    }

    SSL_set_fd(ssl, socket_fd);
    
    if(SSL_connect(ssl) == -1) {
        fprintf(stderr, "SSL_connect() failed.\n");
    }
}

_SSL_connect::~_SSL_connect(){
        SSL_free(ssl);
}

void _SSL_connect::SSL_send_request(char *&request_msg){
    SSL_write(ssl, request_msg, strlen(request_msg));
}

std::string _SSL_connect::SSL_receive_response(char *&buffer){
    SSL_read(ssl, buffer, sizeof(buffer));

    return (std::string) buffer;
}
