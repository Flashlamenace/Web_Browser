#include "../includes/http.hpp"

// Class HTTP.
        
HTTP::HTTP(std::string &&response){

//Essayer d'implémenter avec stringstream ce sera surement plus élégant et plus efficace ... 
    size_t end_of_head      = response.find("\r\n\r\n");
    size_t status_line_curs = response.find("\r\n");
               
    status_line = response.substr(0               , status_line_curs); 
    head        = response.substr(status_line_curs, end_of_head);
    payload     = response.substr(end_of_head     , response.npos);

               /* Je garde ce bout de code pour montrer que ce projet m'as tenu beaucoup trop longtemps éveillé !
                *Hhhm oui les espaces ZZZzzzZZZzz Mauvais ça les espaces ... ZZZzzzzZZZ
                * 
                *size_t space = 0;
                *                 
                *//*Trouver quelque chose de plus propre quand j'aurais dormi ...
                *while ((space = head.find(" ")) != head.npos){
                *    
                *    head.erase(space, 1);
                *
                *}
                */
}

// Class HEADER :
HEADER::HEADER(const std::string &key_1, const std::string &value_1) : key(key_1), value(value_1){};

std::map <std::string, std::string> RESPONSE_HEADER::parse_header_field(std::string &header_field){
    
    std::string key;
    std::string value;
    std::stringstream header_field_stream(header_field);
    std::map <std::string, std::string> header_value_hm;

    while (std::getline(header_field_stream, key, ':')){
        std::getline(header_field_stream, value);
       
        header_value_hm[key] = value; 
    }
    return header_value_hm;
}
