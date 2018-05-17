#ifndef AGENT_H
#define AGENT_H
#include "logic.h"

class Agent{
private:
    int color;
    Logic* logic;
public:
    virtual void send_message(int x,int y);
    virtual void get_message(int x,int y);
};

#endif // AGENT_H

