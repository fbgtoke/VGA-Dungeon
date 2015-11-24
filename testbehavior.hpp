#ifndef TESTBEHAVIOR_HPP
#define TESTBEHAVIOR_HPP

#include "behavior.hpp"

class TestBehavior : public Behavior
{
private:
    CommandDirection dirs[4] = {UP, DOWN, LEFT, RIGHT};
    int i = 0;

public:
    TestBehavior(int id, const CharacterFactory& f) : Behavior(id, f) {};
    Command getCommand()
    {
        return Command(dirs[i], MOVE);
        i = (i+1)%4;
    };
};

#endif // TESTBEHAVIOR_HPP
