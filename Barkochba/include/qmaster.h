#include "node.h"
#include <iostream>

class Qmaster
{
    Node *start;
    Node *current;

public:
    Qmaster(Node *start = nullptr) : start(start), current(start) {}
    void ask()
    {
        std::cout << current->getName() << '?' << std::endl;
    }
    void reset(){
        current = start;
    }
    bool process()
    {
        return current->task(current);
    }
    ~Qmaster()
    {
        delete start;
    }
};