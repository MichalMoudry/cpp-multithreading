#ifndef _REQUEST_H_
#define _REQUEST_H_

#include "header.h"
#include "url.h"
#include <memory>
#include <string>

namespace http {
    class Request final {
    private:
        std::string method;
        std::unique_ptr<Url> url;
        std::string protocol;
        int proto_major;
        int proto_minor;
        Header header;
        //body
        long int content_length;
    };
}

#endif