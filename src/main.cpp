#include "../includes/network.hpp"
#include "../includes/http.hpp"

#include <cstddef>
#include <cstring>
#include <ostream>

//test
int main(void){
 
    std::string url = "http://exemple.org/";
    
    char *response;

    SOCKET Socket;

    char request[] = "GET / HTTP/1.0\r\nHost: example.org\r\nUser-Agent: polypous/0.1\r\n Accept: */*\r\nConnection: close\r\n\r\n";


    char buffer[8096];
    size_t buffer_size = 8096;

    Socket.parse_url(url);
    Socket.what_is_port_proto();

    Socket.connect_to_server();
    Socket.send_request(request);
    
    HTTP Header;
    
return 0;
}

//GET / HTTP/2
//Host: exemple.org
//User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:136.0) Gecko/20100101 Firefox/136.0
//Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
//Accept-Language: en-US,en;q=0.5
//Accept-Encoding: gzip, deflate, br, zstd
//DNT: 1
//Connection: keep-alive
//Upgrade-Insecure-Requests: 1
//Sec-Fetch-Dest: document
//Sec-Fetch-Mode: navigate
//Sec-Fetch-Site: none
//Sec-Fetch-User: ?1
//Sec-GPC: 1
//Priority: u=0, i
