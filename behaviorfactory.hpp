#ifndef BEHAVIORFACTORY_HPP
#define BEHAVIORFACTORY_HPP

#include "behavior.hpp"
#include "testbehavior.hpp"
// include other behaviors

enum BehaviorID {DEFAULT, TEST, NBEHAVIORS};

class BehaviorFactory
{
public:
    static Behavior* getBehavior(BehaviorID b, int id, const CharacterFactory& f)
    {
        switch(id)
        {
        case TEST:
            return new TestBehavior(id, f);
        case DEFAULT:
        default:
            return new Behavior(id, f);
        }
    }
};

#endif // BEHAVIORFACTORY_HPP
