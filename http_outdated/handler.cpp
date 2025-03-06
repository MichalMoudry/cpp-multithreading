namespace http {
class Handler {
public:
    Handler() = default;
    virtual void ServeHTTP() const = 0;
};
}