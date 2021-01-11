#ifndef XUTIL_HPP
#define XUTIL_HPP

#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <conio.h>
#include <windows.h>

typedef std::string String;
typedef std::ofstream oFILE;
typedef std::ifstream iFILE;
using json = nlohmann::json;

String sha256(const String& message) {
    return message;
}

namespace xUtil
{
bool isFileExist(const String &str)
{
    if (!str.empty())
    {
        iFILE read;
        read.open(str);
        if (!read.is_open())
        {
            return false;
        }
        else
        {
            read.close();
            return true;
        }
    }
    else
    {
        return false;
    }
}
bool isDirectoryExist(const String &str)
{
    if (!str.empty())
    {
        DWORD dir = GetFileAttributesA(str.c_str());
        if (dir == INVALID_FILE_ATTRIBUTES)
        {
            return false;
        }
        if (dir & FILE_ATTRIBUTE_DIRECTORY)
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
        return false;
    }
}
inline String StringFormat(const char *fmt, ...)
{
    int size = 512;
    char *buffer = 0;
    buffer = new char[size];
    va_list vl;
    va_start(vl, fmt);
    int nsize = vsnprintf(buffer, size, fmt, vl);
    if (size <= nsize)
    {
        delete[] buffer;
        buffer = 0;
        buffer = new char[nsize + 1];
        nsize = vsnprintf(buffer, size, fmt, vl);
    }
    String ret(buffer);
    va_end(vl);
    delete[] buffer;
    return ret;
}
void MakeDir(const String &dir)
{
    CreateDirectoryA(dir.c_str(), 0);
}
void RemoveFile(const String &fname)
{
    DeleteFileA(fname.c_str());
}
void RemoveDir(const String &dir)
{
    RemoveDirectoryA(dir.c_str());
}
void clrscr()
{
    system("cls");
}
void Pause()
{
    getch();
}
char charget()
{
    return getch();
}
void Pause(size_t ms)
{
    Sleep(ms);
}
} // namespace xUtil
#endif