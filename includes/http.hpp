#include <map>
#include <string>
#include <vector>
#include <sstream>

class HTTP{
        
    private :
        std::string head;
        std::string status_line;     
        std::string payload;        
    public:
        HTTP(std::string &&response);
};

class HEADER{
    private:
            std::string key;
            std::string value;
    public:
            HEADER(const std::string &key_1, const std::string &value_1);
};

class RESPONSE_HEADER {

    private:
            std::map <std::string, std::vector<HEADER>> header_hm;
    public:
            //Take a headerfield as a string as argument and return a hash map of string and vector as arguments. 
            std::map <std::string, std::string>parse_header_field(std::string &header_field);
};
                


