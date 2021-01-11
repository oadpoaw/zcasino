#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP
#include "util/xUtil.hpp"
#include <cctype>
#include <iostream>
bool usernameInputCheck(const String &);
bool passwordInputCheck(const String &);
String maskedInput();
bool CheckDouble(const String &);
bool usernameInputCheck(const String &VALUE)
{
    if (VALUE.empty())
    {
        return false;
    }
    for (size_t i = 0; i < VALUE.length(); i++)
    {
        if (isalnum(VALUE[i]))
        {
            continue;
        }
        else if (VALUE[i] == '_')
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}
bool passwordInputCheck(const String &VALUE)
{
    if (VALUE.length() >= 8)
    {
        return true;
    }
    else
    {
        return false;
    }
}
String maskedInput()
{
    char key;
    String output = "";
    while (true)
    {
        key = xUtil::charget();
        if (key == VK_RETURN)
        {
            break;
        }
        else if (key == VK_BACK)
        {
            if (output.length() > 0)
            {
                std::cout << "\b \b";
                output.erase(output.length() - 1);
            }
        }
        else
        {
            std::cout << "*";
            output += key;
        }
    }
    std::cout << '\n';
    return output;
}
bool CheckDouble(const String &VALUE)
{
    if (VALUE.empty())
    {
        return false;
    }
    for (size_t i = 0; i < VALUE.length(); i++)
    {
        if (isdigit(VALUE[i]))
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    if (std::stod(VALUE) <= 0)
    {
        return false;
    }
    return true;
}
#endif