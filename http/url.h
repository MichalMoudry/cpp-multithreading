#ifndef _URL_H_
#define _URL_H_

#include "user_info.h"
#include <memory>
#include <string>

namespace http {
    class Url final {
    private:
        std::string scheme;
        std::string opaque;
        std::unique_ptr<UserInfo> user;
        std::string host;
        std::string path;
        std::string raw_path;
        bool omit_host;
        bool force_query;
        std::string raw_query;
        std::string fragment;
        std::string raw_fragment;
    };
}

#endif