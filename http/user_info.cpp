#include "user_info.h"

http::UserInfo::UserInfo(const std::string& user_name_arg)
    : user_name(user_name_arg),
    password(""),
    is_password_set(false) {}

http::UserInfo::UserInfo(
    const std::string& user_name_arg,
    const std::string& password_arg)
    : user_name(user_name_arg),
    password(password_arg),
    is_password_set(true) {}

std::string http::UserInfo::get_user_name() const noexcept {
    return user_name;
}

std::pair<std::string, bool> http::UserInfo::get_password() const noexcept {
    return std::pair<std::string, bool>(password, is_password_set);
}

std::string http::UserInfo::to_str() const noexcept {
    return "";
}