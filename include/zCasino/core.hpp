#ifndef CORE_HPP
#define CORE_HPP

#include "zCasino/classes/User.hpp"
#include <windows.h>
#include <iostream>
#include "util/xUtil.hpp"
#include "zCasino/Handlers/InputHandler.hpp"
#include "zCasino/Handlers/Economy.hpp"
#include "zCasino/Games/Gamble.hpp"
#include "zCasino/Games/SlotMachine.hpp"

void Setup();
User Login();
User Signup();
User fMenu();
void Play(User &);
void transfer(User);
void Menu(User &);
void zCasino();

void Setup()
{
    if (!xUtil::isDirectoryExist("accounts"))
    {
        xUtil::MakeDir("accounts");
    }
    if (!xUtil::isDirectoryExist("data"))
    {
        xUtil::MakeDir("data");
    }
    SetConsoleTitleA("zCasino by oadpoaw");
}
User Login()
{
    xUtil::clrscr();
    std::cout << "\n\n\n\n\n";
    std::cout << String(5, '\t') << String(33, '=') << '\n';
    std::cout << String(5, '\t') << "Login to zCasino\n";
    String un, pw;
    std::cout << String(5, '\t') << "Username : ";
    std::getline(std::cin, un, '\n');
    if (!usernameInputCheck(un))
    {
        std::cout << String(5, '\t') << String(33, '=') << '\n';
        std::cout << String(5, '\t') << "You are not allowed to put special characters except underscores\nand you are not allowed to put an empty username.\n";
        xUtil::Pause(3000);
    }
    else
    {
        std::cout << String(5, '\t') << "Password : ";
        pw = maskedInput();
        User retval(un, pw);
        if (!passwordInputCheck(pw))
        {
            std::cout << String(5, '\t') << String(33, '=') << '\n';
            std::cout << String(5, '\t') << "You are not allowed to put passwords less than 8 characters.\n";
        }
        else
        {
            retval.login();
            if (!retval.isLogin())
            {
                std::cout << String(5, '\t') << String(33, '=') << '\n';
                std::cout << String(5, '\t') << "Incorrect Username or Password.\n";
            }
            else
            {
                std::cout << String(5, '\t') << String(33, '=') << '\n';
                std::cout << String(5, '\t') << "Login Success!\n";
            }
        }
        xUtil::Pause(3000);
        return retval;
    }
    User lmao("f", "f");
    return lmao;
}
User Signup()
{
    xUtil::clrscr();
    std::cout << "\n\n\n\n\n";
    std::cout << String(5, '\t') << String(33, '=') << '\n';
    std::cout << String(5, '\t') << "Signup to zCasino\n";
    String un, pw;
    std::cout << String(5, '\t') << "Username : ";
    std::getline(std::cin, un, '\n');
    if (!usernameInputCheck(un))
    {
        std::cout << String(5, '\t') << String(33, '=') << '\n';
        std::cout << String(5, '\t') << "You are not allowed to put special characters except underscores\nand you are not allowed to put an empty username.\n";
        xUtil::Pause(3000);
    }
    else
    {
        std::cout << String(5, '\t') << "Password : ";
        pw = maskedInput();
        User retval(un, pw);
        if (!passwordInputCheck(pw))
        {
            std::cout << String(5, '\t') << String(33, '=') << '\n';
            std::cout << String(5, '\t') << "You are not allowed to put passwords less than 8 characters.\n";
        }
        else
        {
            retval.signup();
            if (!retval.isLogin())
            {
                std::cout << String(5, '\t') << String(33, '=') << '\n';
                std::cout << String(5, '\t') << "An account with that username already exists.\n";
            }
            else
            {
                std::cout << String(5, '\t') << String(33, '=') << '\n';
                std::cout << String(5, '\t') << "Signup Success!\nLogging in...\n";
            }
        }
        xUtil::Pause(3000);
        return retval;
    }
    User lmao("f", "f");
    return lmao;
}
User fMenu()
{
    User temp;
    xUtil::clrscr();
    std::cout << "\n\n\n\n\n";
    std::cout << String(5, '\t') << String(33, '=') << '\n';
    std::cout << String(5, '\t') << "1) Login\n\t\t\t\t\t2) Signup\n";
    std::cout << String(5, '\t') << String(33, '=') << '\n';
    switch (xUtil::charget())
    {
    case '1':
        return Login();
        break;
    case '2':
        return Signup();
        break;
    default:
        break;
    }
    return temp;
}
void Play(User &t)
{
    xUtil::clrscr();
    std::cout << "\n\n\n\n\n";
    Economy p = Economy::getInstance();
    std::cout << String(5, '\t') << String(33, '=') << '\n';
    std::cout << String(5, '\t') << xUtil::StringFormat("Account Balance > %s", std::to_string(p.getBalanceOf(t)).c_str()) << "\n\n";
    std::cout << String(5, '\t') << "1) Gamble\n\t\t\t\t\t2) Slot Machine\n";
    std::cout << String(5, '\t') << String(33, '=') << '\n';
    String bet;
    switch (xUtil::charget())
    {
    case '1':
    {
        std::cout << String(5, '\t') << "You selected Gambling\n\n";
        std::cout << String(5, '\t') << "Bet : ";
        std::getline(std::cin, bet, '\n');
        if (CheckDouble(bet))
        {
            if (std::stod(bet) <= p.getBalanceOf(t))
            {
                Gamble g(t, std::stod(bet));
                g.begin();
                g.update();
                g.end();
            }
            else
            {
                std::cout << String(5, '\t') << String(33, '=') << '\n';
                std::cout << String(5, '\t') << "You can't bet higher than you balance, lmfao\n";
            }
        }
        else
        {
            std::cout << String(5, '\t') << String(33, '=') << '\n';
            std::cout << String(5, '\t') << "You can only bet real numbers, lmao\n";
        }
        xUtil::Pause(4500);
        break;
    }
    case '2':
    {
        std::cout << String(5, '\t') << "You selected Slot Machine\n\n";
        std::cout << String(5, '\t') << "Bet : ";
        std::getline(std::cin, bet, '\n');
        if (CheckDouble(bet))
        {
            if (std::stod(bet) <= p.getBalanceOf(t))
            {
                SlotMachine g(t, std::stod(bet));
                g.begin();
                g.update();
                g.end();
            }
            else
            {
                std::cout << String(5, '\t') << String(33, '=') << '\n';
                std::cout << String(5, '\t') << "You can't bet higher than you balance, lmfao\n";
            }
        }
        else
        {
            std::cout << String(5, '\t') << String(33, '=') << '\n';
            std::cout << String(5, '\t') << "You can only bet real numbers, lmao\n";
        }
        xUtil::Pause(4500);
        break;
    }
    default:
        break;
    }
}
void transfer(User t)
{
    Economy here = Economy::getInstance();
    xUtil::clrscr();
    std::cout << "\n\n\n\n\n";
    std::cout << String(5, '\t') << String(33, '=') << '\n';
    std::cout << String(5, '\t') << xUtil::StringFormat("Account Balance > %s", std::to_string(here.getBalanceOf(t)).c_str()) << "\n\n";
    std::cout << String(5, '\t') << "Enter Amount to send : ";
    String bet;
    std::getline(std::cin, bet, '\n');
    if (CheckDouble(bet))
    {
        String res;
        std::cout << String(5, '\t') << "Enter Recepient : ";
        std::getline(std::cin, res, '\n');
        std::cout << String(5, '\t') << String(33, '=') << '\n';
        switch (here.transact(t, res, std::stod(bet)))
        {
        case 0:
            std::cout << String(5, '\t') << "Transaction Successful!\n";
            break;
        case 1:
            std::cout << String(5, '\t') << "False login.\n";
            break;
        case 2:
            std::cout << String(5, '\t') << "Recepient does not exists.\n";
            break;
        case 3:
            std::cout << String(5, '\t') << "You can only send real numbers, lmfao\n";
            break;
        case 4:
            std::cout << String(5, '\t') << xUtil::StringFormat("Insufficient balance to send %s", bet.c_str()) << '\n';
            break;
        }
    }
    else
    {
        std::cout << String(5, '\t') << String(33, '=') << '\n';
        std::cout << String(5, '\t') << "You can only put numbers, lmao\n";
    }
    xUtil::Pause(4500);
}
void Menu(User &t)
{
    xUtil::clrscr();
    std::cout << "\n\n\n\n\n";
    Economy here = Economy::getInstance();
    std::cout << String(5, '\t') << String(33, '=') << '\n';
    std::cout << String(5, '\t') << xUtil::StringFormat("Account Balance > %s", std::to_string(here.getBalanceOf(t)).c_str()) << "\n\n";
    std::cout << String(5, '\t') << "1) Play\n\t\t\t\t\t2) Send Coins\n\t\t\t\t\t3) Change Password\n\t\t\t\t\t4) Logout\n";
    std::cout << String(5, '\t') << String(33, '=') << '\n';
    switch (xUtil::charget())
    {
    case '1':
    {
        Play(t);
        break;
    }
    case '2':
    {
        transfer(t);
        break;
    }
    case '3':
    {
        xUtil::clrscr();
        std::cout << "\n\n\n\n\n";
        std::cout << String(5, '\t') << String(33, '=') << '\n';
        std::cout << String(5, '\t') << "Confirm old Password : ";
        String lmao = maskedInput();
        std::cout << String(5, '\t') << "New Password : ";
        String lenew = maskedInput();
        if (passwordInputCheck(lenew))
        {
            std::cout << String(5, '\t') << String(33, '=') << '\n';
            if (t.getPassword() == sha256(lmao))
            {
                t.setPassword(lenew);
                std::cout << String(5, '\t') << "New Password saved!\n";
            }
            else
            {
                std::cout << String(5, '\t') << "Incorrect old password, New Password not saved.\n";
            }
        }
        else
        {
            std::cout << String(5, '\t') << "Your new Password cannot be less than 8 characters.\n";
        }
        xUtil::Pause(2500);
        break;
    }
    case '4':
        t.logout();
        break;
    default:
        break;
    }
}
void zCasino()
{
    Economy here = Economy::getInstance();
    Setup();
    while (true)
    {
        User Omg;
        while (true)
        {
            Omg = fMenu();
            if (Omg.isLogin())
            {
                break;
            }
        }
        if (Omg.isLogin())
        {
            here.add(Omg, 500);
        }
        while (Omg.isLogin())
        {
            Menu(Omg);
        }
    }
}
#endif