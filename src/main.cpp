#include "../includes/network.hpp"

#include <cstddef>
#include <cstring>
#include <ostream>

int main(void){
 
    std::string url = "http://exemple.org/";
    
    char *response;

    SOCKET Socket;

    const char *source = "GET / HTTP/1.0\r\nHost: example.org\r\nUser-Agent: polypous/0.1\r\n Accept: */*\r\nConnection: keep-alive\r\n\r\n";
    size_t length = strlen(source);
    char *request = (char *)malloc((length + 1) * sizeof(char)); // Allocate memory

    if (request == nullptr) {
        // Handle memory allocation failure
        std::cerr << "Memory allocation failed!" << std::endl;
        return 1;
    }

    // Copy the string into the allocated memory
    strcpy(request, source);

    char buffer[4096];
    size_t buffer_size = 4096;

    Socket.parse_url(url);
    Socket.what_is_port_proto();

    Socket.connect_to_server();
    Socket.send_request(request);
    
    std::cout << Socket.receive_request(buffer, buffer_size) << std::endl << std::endl;

    free(request);
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
