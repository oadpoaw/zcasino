#ifndef USER_HPP
#define USER_HPP
#include "util/xUtil.hpp"
class User
{
private:
    json data;
    bool session;
    void saveAttributes();

public:
    User();
    User(const String &, const String &);
    void setUsername(const String &);
    void setPassword(const String &);
    String getUsername() const;
    String getPassword() const;
    String getAddress() const;
    String toString() const;
    json toJson() const;
    void login();
    void logout();
    void signup();
    bool isLogin() const;
    ~User();
};
void User::saveAttributes()
{
    oFILE write;
    write.open(getAddress(), std::ios::trunc);
    write << data.dump(4);
    write.close();
}
User::User()
{
    this->data["username"] = "";
    this->data["password"] = "";
    this->session = false;
}
User::User(const String &un, const String &pw)
{
    this->data["username"] = un;
    this->data["password"] = sha256(pw);
    this->session = false;
}
void User::setUsername(const String &un)
{
    if (this->isLogin())
    {
        this->data["username"] = un;
        xUtil::RemoveFile(getAddress());
        saveAttributes();
    }
}
void User::setPassword(const String &pw)
{
    if (this->isLogin())
    {
        this->data["password"] = sha256(pw);
        saveAttributes();
    }
}
String User::getUsername() const
{
    return data["username"].get<String>();
}
String User::getPassword() const
{
    return data["password"].get<String>();
}
String User::getAddress() const
{
    return xUtil::StringFormat("accounts/%s.json", data["username"].get<String>().c_str());
}
String User::toString() const
{
    return data["username"].get<String>();
}
json User::toJson() const
{
    return data;
}
void User::login()
{
    if (xUtil::isFileExist(getAddress()) && !session)
    {
        iFILE read;
        read.open(getAddress(), std::ios::in);
        json j = json::parse(read);
        read.close();
        if (j["password"].get<String>() == getPassword())
        {
            this->session = true;
        }
    }
}
void User::logout()
{
    this->session = false;
}
void User::signup()
{
    if (!xUtil::isFileExist(getAddress()) && !session)
    {
        saveAttributes();
        this->session = true;
    }
}
bool User::isLogin() const
{
    return session;
}
User::~User()
{
    this->data = nullptr;
}
#endif