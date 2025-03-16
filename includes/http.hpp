#pragma once

#include <map>
#include <string>


enum Method
{
             //+---------+-------------------------------------------------+-------+
             //+---------+-------------------------------------------------+-------+
             //| Method  | Description                                     | Sec.  |
             //+---------+-------------------------------------------------+-------+
    GET,     //| GET     | Transfer a current representation of the target | 4.3.1 |
    HEAD,    //|         | resource.                                       |       |
    POST,    //| HEAD    | Same as GET, but only transfer the status line  | 4.3.2 |
    PUT,     //|         | and header section.                             |       |
    DELETE,  //| POST    | Perform resource-specific processing on the     | 4.3.3 |
    CONNECT, //|         | request payload.                                |       |
    OPTIONS, //| PUT     | Replace all current representations of the      | 4.3.4 |
    TRACE    //|         | target resource with the request payload.       |       |
             //| DELETE  | Remove all current representations of the       | 4.3.5 |
             //|         | target resource.                                |       |
             //| CONNECT | Establish a tunnel to the server identified by  | 4.3.6 |
             //|         | the target resource.                            |       |
             //| OPTIONS | Describe the communication options for the      | 4.3.7 |
             //|         | target resource.                                |       |
             //| TRACE   | Perform a message loop-back test along the path | 4.3.8 |
             //|         | to the target resource.                         |       |
             //+---------+-------------------------------------------------+-------+
};

enum Protocol_v{
    HTTP_1_0,
    HTTP_1_1,
    HTTP_2_0
};

namespace To_String{
std::string to_string(Method method);
std::string to_string(Protocol_v protocol);
};

class HTTP{
    private :
        std::string start_line;                
        std::string head;
        std::string payload;        
    public:
        HTTP(std::string &&response);
        HTTP(std::string &&start_line, std::string &&header);

        std::string get_head();
        std::string get_start_line();
        std::string get_payload();

        std::string set_head       (std::string &head_1);
        std::string set_start_line (std::string &start_line_1);
        std::string set_payload    (std::string &payload_1);
};

class REQUEST : public HTTP{
    private:
        static std::string construct_request_line(Method &method, std::string &path_to_r, Protocol_v &protocol_version);
        static std::string construct_header      (std::string &host);
 
        
        //Request line :
        Method method;
        Protocol_v protocol_version;
        std::string path_to_r;
        std::string host;
        std::string request;
        //Header :
        
    public: 
        REQUEST(Method &&method, std::string &&path_to_r, Protocol_v &&protocol_version, std::string &&host);
        std::string get_request();
};

class RESPONSE : public HTTP{
    private:
        std::map <std::string, std::string> header_hm;
    public: 
           RESPONSE(std::string &&response);
};
