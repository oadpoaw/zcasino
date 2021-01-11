#ifndef GAME_HPP
#define GAME_HPP
class Game
{
public:
    virtual ~Game() = default;
    virtual void begin() = 0;
    virtual void update(...) = 0;
    virtual void end() = 0;
};
#endif