#ifndef _HANDLER_H_
#define _HANDLER_H_

namespace http {
    class Handler {
    public:
        Handler() = default;
        virtual void serve_http() const = 0;
    };
}
#endif