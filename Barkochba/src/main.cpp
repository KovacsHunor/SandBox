#include "qmaster.h"
#include <stdlib.h>

int main()
{
    bool end = false;
    Node *start = new Node("tárgy");
    start->setNo(new Node("pingvin"));
    start->setYes(new Node("asztal"));

    Qmaster master(start);
    while (!end)
    {
        master.ask();
        if(master.process()){
            master.reset();
            std::cout << "mégegyszer?" << std::endl;
            std::string str;
            std::cin >> str;
            if(str == "nem"){
                end = true;
            }
            system("clear");
        };
    }
    return 0;
}