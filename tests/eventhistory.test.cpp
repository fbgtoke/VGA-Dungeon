#include "eventhistory.hpp"

int main(int argc, char** argv)
{
    std::cout << "Instantiating EventHistory" << std::endl;
    EventHistory h;
    std::cout << "EventHistory instantiated" << std::endl;

    int op = 0;
    do
    {
        std::cout << "Type operation" << std::endl;
        std::cin >> op;

        switch (op)
        {
        case 1:
            std::cout << "New turn selected" << std::endl;
            h.pushEvent(NEWTURN, -1);
            std::cout << "Current turn: #" << h.getCurrentTurn() << std::endl;
            break;
        case 2:
            std::cout << "Idle selected" << std::endl;
            h.pushEvent(CIDLE, 0);
            break;
        case 3:
            std::cout << "Move selected" << std::endl;
            h.pushEvent(CMOVE, 0);
            break;
        case 4:
            std::cout << "Attack selected" << std::endl;
            h.pushEvent(CATTACK, 0);
            break;
        case 5:
            std::cout << "Character spawn selected" << std::endl;
            h.pushEvent(CSPAWN, 0);
            break;
        case 6:
            std::cout << "Undo!" << std::endl;
            h.undoLastEvent();
            break;
        case 7:
            h.printAllEvents();
            break;
        default:
            break;
        }
    } while (op != -1);
}
