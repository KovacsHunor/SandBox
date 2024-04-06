#include "qmaster.h"
#include <stdlib.h>

int main()
{
    bool end = false;

    Qmaster master;
    while (!end)
    {
        master.ask();
        if(master.process()){
            master.reset();
            std::cout << "mégegyszer?" << std::endl;
            std::string str;
            getline(std::cin, str);
            if(str == "nem"){
                end = true;
            }
            //system("clear");
        };
    }
    return 0;
}