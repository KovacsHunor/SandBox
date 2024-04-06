#include "node.h"
#include <iostream>

class Qmaster
{
    Node *start;
    Node *current;

public:
    Qmaster(Node *start = nullptr) : start(start){
        load();
        current = this->start;
    }
    void write(Node* c, std::ofstream & file);
    void build(Node* &c, std::ifstream & file);
    void save();
    void load();
    void ask()
    {
        std::cout << current->getName() << '?' << std::endl;
    }
    void reset(){
        current = start;
        save();
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