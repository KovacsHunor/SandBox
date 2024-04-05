#include <iostream>

class Node
{
protected:
    std::string name;
    Node *no;
    Node *yes;
public:
    Node(std::string name, Node* no = nullptr, Node* yes = nullptr) : name(name), no(no), yes(yes) {}
    std::string getName()
    {
        return name;
    }
    bool isLeaf() { return no == nullptr && yes == nullptr; }
    void setName(std::string str)
    {
        name = str;
    }
    void setYes(Node *n)
    {
        yes = n;
    }
    void setNo(Node *n)
    {
        no = n;
    }
    void set(Node *y, Node *n)
    {
        yes = y;
        no = n;
    }
    void finalTask(bool yes)
    {
        Node* l = yes?getYes():getNo();
        std::string str;
        std::cout << l->getName() << '?' << std::endl;
        std::cin >> str;
        if (str == "nem")
        {
            std::cout << "mire gondoltál?\n";
            std::cin >> str;
            Node *leaf = new Node(str);

            std::cout << "milyen eddig nem elhangzott kérdés igaz rá, ami nem igaz erre: \"" << l->getName() << "\"?" << std::endl;
            std::cin >> str;
            Node *gate = new Node(str);

            gate->setNo(l);
            gate->setYes(leaf);
            yes?setYes(gate):setNo(gate);

        }
    }
    bool task(Node* &current)
    {
        std::string str;
        std::cin >> str;

        if (str == "nem")
        {
            if (getNo()->isLeaf())
            {
                finalTask(false);
                return true;
            }
            else{
                current = no;
            }
        }
        else if (str == "igen")
        {
            if (getYes()->isLeaf())
            {
                finalTask(true);
                return true;
            }
            else{
                current = yes;
            }
        }
        return false;
    }
    Node *getYes() { return yes; }
    Node *getNo() { return no; }

    virtual ~Node()
    {
        delete yes;
        delete no;
    }
};