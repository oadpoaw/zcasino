#ifndef ECONOMY_HPP
#define ECONOMY_HPP
typedef double Coins;
#include "util/xUtil.hpp"
#include "zCasino/classes/User.hpp"
class Economy
{
public:
    static Economy &getInstance();
    ~Economy();

    void add(const User, const Coins);
    void remove(const User, const Coins);
    void set(const User, const Coins);
    Coins getBalanceOf(const User);
    String getAddressOf(const User);
    bool isSufficientOf(const User, const Coins);
    int transact(const User, const String &, const Coins);
    Economy(Economy &) = default;

private:
    Economy();
    Economy &operator=(Economy &) = default;
    json getAttributesOf(const User);
    void setAttributesOf(const User, const json);
};
Economy &Economy::getInstance()
{
    static Economy instance;
    return instance;
}
Economy::Economy()
{
}
Economy::~Economy()
{
}
String Economy::getAddressOf(const User user)
{
    return xUtil::StringFormat("data/%s.json", user.getUsername().c_str());
}
json Economy::getAttributesOf(const User user)
{
    iFILE read;
    read.open(getAddressOf(user));
    json retval = json::parse(read);
    read.close();
    return retval;
}
void Economy::setAttributesOf(const User user, const json j)
{
    oFILE write;
    write.open(getAddressOf(user), std::ios::trunc);
    write << j.dump(4);
    write.close();
}
void Economy::add(const User user, const Coins val)
{
    if (!user.isLogin())
    {
        return;
    }
    if (xUtil::isFileExist(getAddressOf(user)))
    {
        json a = getAttributesOf(user);
        a["balance"] = a["balance"].get<Coins>() + val;
        setAttributesOf(user, a);
    }
    else
    {
        json b = {
            {"balance", Coins(0.0)}};
        b["balance"] = b["balance"].get<Coins>() + val;
        setAttributesOf(user, b);
    }
}
void Economy::remove(const User user, const Coins val)
{
    if (!user.isLogin())
    {
        return;
    }
    if (xUtil::isFileExist(getAddressOf(user)))
    {
        json a = getAttributesOf(user);
        a["balance"] = a["balance"].get<Coins>() - val;
        setAttributesOf(user, a);
    }
    else
    {
        json b = {
            {"balance", Coins(0.0)}};
        b["balance"] = b["balance"].get<Coins>() - val;
        setAttributesOf(user, b);
    }
}
void Economy::set(const User user, const Coins val)
{
    if (!user.isLogin())
    {
        return;
    }
    if (xUtil::isFileExist(getAddressOf(user)))
    {
        json a = getAttributesOf(user);
        a["balance"] = val;
        setAttributesOf(user, a);
    }
    else
    {
        json b = {
            {"balance", val}};
        setAttributesOf(user, b);
    }
}
Coins Economy::getBalanceOf(const User user)
{
    if (!user.isLogin())
    {
        return -0x7FFF;
    }
    if (xUtil::isFileExist(getAddressOf(user)))
    {
        return getAttributesOf(user)["balance"].get<Coins>();
    }
    else
    {
        json b = {
            {"balance", Coins(0.0)}};
        setAttributesOf(user, b);
        return b["balance"].get<Coins>();
    }
}
bool Economy::isSufficientOf(const User user, const Coins val)
{
    if (!user.isLogin())
    {
        return false;
    }
    if (xUtil::isFileExist(getAddressOf(user)))
    {
        if (val <= getAttributesOf(user)["balance"].get<Coins>())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        json b = {
            {"balance", Coins(0.0)}};
        setAttributesOf(user, b);
        return false;
    }
}
/**
 * 0 = success 
 * 1 = user not allowed to transact
 * 2 = recepient not found
 * 3 = cant send less than or equal to zero
 * 4 = user is insufficient to send with that amount
*/
int Economy::transact(const User p, const String &res, const Coins amount)
{
    if (!p.isLogin())
    {
        return 1;
    }
    if (xUtil::isFileExist(xUtil::StringFormat("data/%s.json", res.c_str())))
    {
        if (amount <= 0)
        {
            return 3;
        }
        else
        {
            if (isSufficientOf(p, amount))
            {
                remove(p, amount);
                iFILE read;
                read.open(xUtil::StringFormat("data/%s.json", res.c_str()));
                json ress = json::parse(read);
                read.close();
                ress["balance"] = ress["balance"].get<Coins>() + amount;
                oFILE write;
                write.open(xUtil::StringFormat("data/%s.json", res.c_str()), std::ios::out);
                write << ress.dump(4);
                write.close();
                return 0;
            }
            else
            {
                return 4;
            }
        }
    }
    else
    {
        return 2;
    }
}
#endif