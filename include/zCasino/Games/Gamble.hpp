#ifndef GAMBLE_HPP
#define GAMBLE_HPP
#include "util/xUtil.hpp"
#include "zCasino/classes/Game.hpp"
#include "zCasino/Handlers/Economy.hpp"
#include "zCasino/classes/User.hpp"
#include "util/Chance.hpp"
#include "util/Random.hpp"
#include <iostream>
class Gamble : public Game
{
private:
    User data;
    Coins bet;
    Coins prize;
    bool isWon;
    size_t MR;
    size_t HR;

public:
    Gamble(const User, const Coins);
    void begin() override;
    void update(...) override;
    void end() override;
};
Gamble::Gamble(const User user, const Coins val)
{
    this->data = user;
    this->bet = val;
    this->prize = 0;
    this->isWon = true;
}
void Gamble::begin()
{
    this->MR = Random<size_t>(12);
    this->HR = Random<size_t>(12);
    std::cout << String(5, '\t') << String(33, '=') << '\n';
    std::cout << String(5, '\t') << "You roled : " << MR << '\n';
    std::cout << String(5, '\t') << "Bot roled : " << HR << '\n';
    std::cout << String(5, '\t') << String(33, '=') << '\n';
    xUtil::Pause(1500);
}
void Gamble::update(...)
{
    if (MR > HR)
    {
        this->prize = bet + ((Coins(MR) + Coins(HR)));
        if (getChanceOf(15))
        {
            Coins aa = bet + (Coins(MR) + Coins(HR)) * 2;
            this->prize += aa * 3;
            std::cout << String(5, '\t') << "+" << std::to_string(aa * 3) << " (15%)\n";
        }
        if (getChanceOf(10))
        {
            Coins bb = bet + ((Coins(MR) + Coins(HR) * 3));
            this->prize += bb * 6;
            std::cout << String(5, '\t') << "+" << std::to_string(bb * 6) << " (10%)\n";
        }
        if (getChanceOf(5))
        {
            Coins cc = prize * 6;
            this->prize += cc;
            std::cout << String(5, '\t') << "+" << std::to_string(cc) << " (5%)\n";
        }
    }
    else
    {
        this->isWon = false;
    }
}
void Gamble::end()
{
    Economy here = Economy::getInstance();
    if (isWon)
    {
        std::cout << String(5, '\t') << "You Won a total of " << std::to_string(prize) << " coins.\n...\n";
        here.add(data, prize);
    }
    else
    {
        std::cout << String(5, '\t') << "You lost " << std::to_string(bet) << " coins.\n...\n";
        here.remove(data, bet);
    }
}
#endif