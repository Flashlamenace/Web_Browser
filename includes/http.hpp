#include <map>
#include <string>

class HTTP{
        
    private :
        std::string head;
        std::string status_line;     
        std::string payload;        
    public:
        HTTP(std::string &&response){
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
};

class HEADER : public HTTP {
    private :
        std::map<std::string, std::string> header_map;
    public: 
    //En faire un constructeur ? En soit il va aussi une classe pour décrire les header http ...
        std::map <std::string, std::string> associate_key_value(std::string &header_part){
            
            return header_map;
        }
};
                


