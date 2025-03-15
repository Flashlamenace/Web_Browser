#pragma once

#include <map>
#include <string>
#include <sstream>

enum Method
{
GET,
HEAD,
POST,
PUT,
DELETE,
CONNECT,
OPTION,
TRACE
/*
   +---------+-------------------------------------------------+-------+
   | Method  | Description                                     | Sec.  |
   +---------+-------------------------------------------------+-------+
   | GET     | Transfer a current representation of the target | 4.3.1 |
   |         | resource.                                       |       |
   | HEAD    | Same as GET, but only transfer the status line  | 4.3.2 |
   |         | and header section.                             |       |
   | POST    | Perform resource-specific processing on the     | 4.3.3 |
   |         | request payload.                                |       |
   | PUT     | Replace all current representations of the      | 4.3.4 |
   |         | target resource with the request payload.       |       |
   | DELETE  | Remove all current representations of the       | 4.3.5 |
   |         | target resource.                                |       |
   | CONNECT | Establish a tunnel to the server identified by  | 4.3.6 |
   |         | the target resource.                            |       |
   | OPTIONS | Describe the communication options for the      | 4.3.7 |
   |         | target resource.                                |       |
   | TRACE   | Perform a message loop-back test along the path | 4.3.8 |
   |         | to the target resource.                         |       |
   +---------+-------------------------------------------------+-------+ */
};

class HTTP{
    private :
        std::string status_line;                
        std::string request_line;
        std::string head;
        std::string payload;        
    public:
        HTTP(std::string &&response);
        HTTP();

        std::string get_head();
        std::string get_status_line();
        std::string get_payload();

        std::string set_head       (std::string &head_1);
        std::string set_status_line(std::string &status_line_1);
        std::string set_payload    (std::string &payload_1);
};

class RESPONSE_HEADER{
    private:
            public:
        std::map <std::string, std::string>parse_header_field(std::string &header_field);
};
           
class REQUEST : public HTTP{
    private:
        //Request line :
        std::string method;
        std::string request_target; 
        std::string protocol_version;
        //Header :
        
    public: 
        REQUEST();
};

class RESPONSE : public HTTP{
    private:
        std::map <std::string, std::string> header_hm;
    public: 
           RESPONSE(std::string &&response);
};
