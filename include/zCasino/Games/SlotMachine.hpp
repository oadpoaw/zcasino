#ifndef SLOTMACHINE_HPP
#define SLOTMACHINE_HPP
#include "util/xUtil.hpp"
#include "zCasino/classes/Game.hpp"
#include "zCasino/Handlers/Economy.hpp"
#include "zCasino/classes/User.hpp"
#include "util/Random.hpp"
#include "util/Chance.hpp"
#include <iostream>
class SlotMachine : public Game
{
private:
    User data;
    Coins bet;
    Coins prize;
    bool isWon;
    size_t a;
    size_t b;
    size_t c;

public:
    SlotMachine(const User, const Coins);
    void begin() override;
    void update(...) override;
    void end() override;
};
SlotMachine::SlotMachine(const User user, const Coins val)
{
    this->data = user;
    this->bet = val;
    this->prize = 0;
    this->isWon = true;
}
void SlotMachine::begin()
{
    this->a = Random<size_t>(6);
    this->b = Random<size_t>(6);
    this->c = Random<size_t>(6);
    std::cout << String(5, '\t') << String(33, '=') << '\n';
    std::cout << String(5, '\t') << xUtil::StringFormat("Results : [%s] [%s] [%s]", std::to_string(a).c_str(), std::to_string(b).c_str(), std::to_string(c).c_str()) << '\n';
    std::cout << String(5, '\t') << String(33, '=') << '\n';
    xUtil::Pause(1500);
}
void SlotMachine::update(...)
{
    if (a == b && b == c)
    {
        this->prize = (bet * 2) + (Coins(a) + Coins(b) + Coins(c));
    }
    else if (a == b || a == c || b == c)
    {
        this->prize = bet + (Coins(a) + Coins(b) + Coins(c));
    }
    else
    {
        this->isWon = false;
    }
    if (isWon)
    {
        if (getChanceOf(15))
        {
            Coins aa = bet + (Coins(a) + Coins(b) + Coins(c)) * 3;
            this->prize += aa * 3;
            std::cout << String(5, '\t') << "+" << std::to_string(aa * 3) << " (15%)\n";
        }
        if (getChanceOf(10))
        {
            Coins bb = bet + ((Coins(a) + Coins(b) + Coins(c)) * 2);
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
}
void SlotMachine::end()
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