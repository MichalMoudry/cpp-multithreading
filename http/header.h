#ifndef _HEADER_H_
#define _HEADER_H_

#include <vector>
#include <utility>
#include <string>

namespace http {
    class Header final {
    private:
        std::vector<std::pair<std::string, std::vector<std::string>>> map;
    public:
        void add(std::string key, std::string value);
        void set(std::string key, std::string value);
        std::string get(std::string key);
        std::vector<std::string> get_values(std::string key);
    };
}

#endif