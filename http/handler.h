#ifndef _HANDLER_H_
#define _HANDLER_H_

namespace http {
    class Handler {
    public:
        Handler() = default;
        virtual void ServeHTTP() const = 0;
    };
}
#endif