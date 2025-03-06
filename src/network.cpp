#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>

class NETWORKING {
    private:
        
    public:
        int create_socket(){
            int socket_fd = 0;

            if ((socket_fd = socket(AF_INET, SOCK_STREAM,0)) < 0) {
                std::cerr << "Can't create the socket !";
            return -1;
            }

        return socket_fd;
}
};