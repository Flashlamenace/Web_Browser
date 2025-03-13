#include <string>
#include <iostream>
#include <vector>

class HTTP{
        
    private :
        std::string head;
        std::string status_line;
        std::string payload;   
        std::vector <std::string> header_line;
     
    public:
        //Il me faut un objet ligne que je puisse tokeniser en pair : clef, valeur.
            std::string set_head(std::string &&response){

                size_t end_of_head      = response.find("\r\n\r\n");
                size_t status_line_curs = response.find("\r\n");
                
                status_line = response.substr(0, status_line_curs); 
                head        = response.substr(status_line_curs, end_of_head);
                
                //seg fault !!!
                std::string resulting_head = head;

                while(resulting_head != "\r\n\r\n"){
                    
                    int i = 0;

                    size_t end_of_line = resulting_head.find("\r\n");
                    header_line.push_back(resulting_head.substr(header_line[i].size(), end_of_line ));

                    i++;

                    std::cout << header_line[i] << std::endl;
                }

                return status_line;                   
        }
};
