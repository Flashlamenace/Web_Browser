#include "../includes/http.hpp"

#include <iostream>
#include <sstream>

std::string to_string(Method method){
    switch(method)
    {
        case Method::GET:
            return "GET";
        case Method::HEAD:
            return "HEAD";
        case Method::POST:
            return "POST";
        case Method::PUT:
            return "PUT";
        case Method::DELETE:
            return "DELETE";
        case Method::TRACE:
            return "TRACE";
        case Method::OPTIONS:
            return "OPTIONS";
        case Method::CONNECT:
            return "CONNECT";
    }
}

std::string to_string( Protocol_v protocol){
    switch(protocol)
    {
        case Protocol_v::HTTP_1_0:
            return "HTTP/1.0";

        case Protocol_v::HTTP_1_1:
            return "HTTP/1.1";

        case Protocol_v::HTTP_2_0:
            return "HTTP/2.0";
    }
}

// Class HTTP.
        
HTTP::HTTP(std::string &&response){

    size_t end_of_head     = response.find("\r\n\r\n");
    size_t start_line_curs = response.find("\r\n");
               
    start_line  = response.substr(0               , start_line_curs); 
    head        = response.substr(start_line_curs, end_of_head);
    payload     = response.substr(end_of_head     , response.npos);
}

HTTP::HTTP( std::string &&request_line, std::string &&header) : start_line(request_line), head(header) {}

std::string HTTP::get_head       (){return head;}
std::string HTTP::get_start_line (){return start_line;}
std::string HTTP::get_payload    (){return payload;}

std::string HTTP::set_head       (std::string &head_1)      {return head = head_1;}
std::string HTTP::set_start_line (std::string &start_line_1){return start_line = start_line_1;}
std::string HTTP::set_payload    (std::string &payload_1)   {return payload = payload_1;}


/******************************************************************************************************************************************************************************/

//Class REQUEST :
REQUEST::REQUEST(Method &&method, std::string &&path_to_r, Protocol_v &&protocol_version, std::string &&host) :
        HTTP(construct_request_line(method, path_to_r, protocol_version), construct_header(host)), 
        method(method), path_to_r(path_to_r), 
        protocol_version(protocol_version)
        {
            request = construct_request_line(method, path_to_r, protocol_version)
             + construct_header(host);

            std::cout << std::endl << request << std::endl;
        }

std::string REQUEST::get_request(){return request;}

std::string REQUEST::construct_request_line(Method &method, std::string &path_to_r, Protocol_v &protocol_version){
    
    std::stringstream request_line_ss("");
        
    request_line_ss
    << to_string(method) 
    << " " 
    << path_to_r 
    << " " 
    << to_string(protocol_version)
    << "\r\n";

return request_line_ss.str();
}

std::string REQUEST::construct_header(std::string &host){
    
    std::stringstream header_ss("");
    
    header_ss << "Host:" 
    << host 
    << "\r\n" 
    << "User-Agent: Polypous/0.1" 
    << "\r\n" 
    << "Connection: close" 
    << "\r\n" 
    << "Accept: */*"
    << "\r\n\r\n";

return header_ss.str();
}

/******************************************************************************************************************************************************************************/

//Class RESPONSE :

RESPONSE::RESPONSE(std::string &&response) : HTTP(std::move(response)){

    std::string key;
    std::string value;
    std::stringstream header_field_stream(get_head());

    while(std::getline(header_field_stream, key, ':')){
          std::getline(header_field_stream, value);
       
        header_hm[key] = value; 
    }
};

