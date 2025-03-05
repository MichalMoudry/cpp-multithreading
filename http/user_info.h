#ifndef _USERINFO_H_
#define _USERINFO_H_

#include <string>
#include <utility>

namespace http {
    class UserInfo final {
    private:
        std::string user_name;
        std::string password;
        bool is_password_set;
    public:
        UserInfo(const std::string& user_name_arg);
        UserInfo(
            const std::string& user_name_arg,
            const std::string& password_arg
        );

        std::string get_user_name() const noexcept;
        std::pair<std::string, bool> get_password() const noexcept;
        std::string to_str() const noexcept;
    };
}

#endif