#include "../includes/network.hpp"
#include "../includes/http.hpp"

#include <cstddef>
#include <cstring>
#include <iostream>



int main(void){
    REQUEST Request(GET, "/", HTTP_1_1, "exemple.org");
    URL Url("http://exemple.org");    
    SOCKET Socket(Url);
    
    char *response;

    char buffer[8096];
    size_t buffer_size = 8096;


    Socket.send_request(Request.get_request().data());
    std::cout << "response : " << Socket.receive_request(buffer, buffer_size) << std::endl ;
    
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
