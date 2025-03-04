#ifndef _SERVER_H_
#define _SERVER_H_

#include <chrono>
#include <string>

namespace http {
    class Server final {
    private:
        std::string addr;
        //http::Handler handler;
        std::chrono::seconds read_timeout;
        std::chrono::seconds write_timout;
        int max_header_size;
    public:
        Server();
        Server(
            const std::string& addr_arg,
            const std::chrono::duration<long long>& read_timeout_arg,
            const std::chrono::duration<long long>& write_timout_arg,
            int max_header_size_arg
        );
    };
}
#endif