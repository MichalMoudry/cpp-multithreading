#ifndef _HTTP_H_
#define _HTTP_H_

#include "handler.h"
#include <string>

namespace http {
    void listen_and_serve(
        const std::string&& addr,
        const http::Handler& handler
    );
}

#endif