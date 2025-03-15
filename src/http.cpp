#include "../includes/http.hpp"

// Class HTTP.
        
HTTP::HTTP(std::string &&response) : request_line({}){

    size_t end_of_head      = response.find("\r\n\r\n");
    size_t status_line_curs = response.find("\r\n");
               
    status_line = response.substr(0               , status_line_curs); 
    head        = response.substr(status_line_curs, end_of_head);
    payload     = response.substr(end_of_head     , response.npos);
}

HTTP::HTTP(){}

std::string HTTP::get_head       (){return head;}
std::string HTTP::get_status_line(){return status_line;}
std::string HTTP::get_payload    (){return payload;}

std::string HTTP::set_head       (std::string &head_1)       {return head = head_1;}
std::string HTTP::set_status_line(std::string &status_line_1){return status_line = status_line_1;}
std::string HTTP::set_payload    (std::string &payload_1)    {return payload = payload_1;}


/******************************************************************************************************************************************************************************/

//Class REQUEST :


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

