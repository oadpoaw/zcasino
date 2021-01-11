#ifndef RANDOM_HPP
#define RANDOM_HPP
#include <ctime>
#include <cstdlib>
namespace oadRandom
{
class oadpoawRandom
{
public:
    oadpoawRandom()
    {
        time_t now = std::time(0);
        tm *t = localtime(&now);
        srand((1900 + t->tm_year) + t->tm_mday + (1 + t->tm_mon) + t->tm_hour + t->tm_min + t->tm_sec);
    }
    ~oadpoawRandom() {}
} oh_boi;
} // namespace oadRandom
template <typename T>
T Random(T max = 0x7FFF)
{
    return rand() % max + 1;
}
#endif