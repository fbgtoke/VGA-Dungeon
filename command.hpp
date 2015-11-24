#ifndef COMMAND_HPP
#define COMMAND_HPP

enum CommandDirection {UP, DOWN, LEFT, RIGHT};
enum CommandType {IDLE, MOVE, ATTACK};

class Command
{
private:
    CommandDirection dir;
    CommandType type;

public:
    Command();
    Command(CommandDirection d, CommandType t);
    ~Command();

    CommandDirection getDirection() const;
    CommandType getType() const;

    void setDirection(CommandDirection d);
    void setType(CommandType t);

    static const Command DEFAULT;
};

#endif // COMMAND_HPP
