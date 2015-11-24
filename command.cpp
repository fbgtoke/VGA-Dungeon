#include "command.hpp"

Command::Command() { dir = UP; type = IDLE; }
Command::Command(CommandDirection d, CommandType t) : dir(d), type(t) {}
Command::~Command() {}

CommandDirection Command::getDirection() const { return dir; }
CommandType Command::getType() const { return type; }

void Command::setDirection(CommandDirection d) { dir = d; }
void Command::setType(CommandType t) { type = t; }

const Command Command::DEFAULT = Command(UP, IDLE);
