#include <iostream>
#include <regex>
#include <string>

class URL {
private:
    std::string protocol;
    std::string host;
    std::string port;
    std::string path;
    std::string query;
    std::string fragment;
public:
     // Getters
     std::string getProtocol() const { return protocol; }
     std::string getHost() const { return host; }
     std::string getPort() const { return port; }
     std::string getPath() const { return path; }
     std::string getQuery() const { return query; }
     std::string getFragment() const { return fragment; }

    static URL parse(const std::string& url) {
        std::regex urlRegex(R"((https?|ftp)://([^/:]+)(:([0-9]+))?(/[^?#]*)?(\?([^#]*))?(#(.*))?)");
        std::smatch matches;

        URL parsedURL;

        if (std::regex_match(url, matches, urlRegex)) {
            parsedURL.protocol = matches[1].str(); // Protocol
            parsedURL.host = matches[2].str();     // Host
            parsedURL.port = matches[4].str();     // Port (if present)
            parsedURL.path = matches[5].str();     // Path (if present)
            parsedURL.query = matches[7].str();    // Query (if present)
            parsedURL.fragment = matches[9].str();  // Fragment (if present)
        } else {
            std::cerr << "Invalid URL format." << std::endl;
        }

        return parsedURL;
    }

   /* void print() const {
        std::cout << "Protocol: " << protocol << std::endl;
        std::cout << "Host: " << host << std::endl;
        std::cout << "Port: " << port << std::endl;
        std::cout << "Path: " << path << std::endl;
        std::cout << "Query: " << query << std::endl;
        std::cout << "Fragment: " << fragment << std::endl;
    }*/
};


