#include "handler.h"
#include <chrono>
#include <string>

namespace http {
class Server final {
    std::string addr;
    http::Handler handler;
    std::chrono::seconds read_timeout;
    std::chrono::seconds write_timout;
    int max_header_size;
public:
    Server()
        : addr(":8080"),
        max_header_size(1 << 20),
        read_timeout(std::chrono::seconds(10)),
        write_timout(std::chrono::seconds(10)) {}

    Server(
        const std::string& addr_arg,
        const std::chrono::duration<long long>& read_timeout_arg,
        const std::chrono::duration<long long>& write_timout_arg,
        int max_header_size_arg
    ) : addr(addr_arg),
        read_timeout(read_timeout_arg),
        write_timout(write_timout_arg),
        max_header_size(max_header_size_arg) {}
};
}