#include <iostream>
#include "Stopwatch.h"

Stopwatch* Stopwatch::instance = nullptr;

int main(){
    std::cout << CLOCKS_PER_SEC << std::endl;

    // Stopwatch *s = s->getInstance();
    // Superior
    Stopwatch *s = Stopwatch::getInstance();

    std::cout << s->getElapsedTime() << std::endl;

    int i = 1;
    while (i < 20)
    {
        if (s->getElapsedTime() > i){
            std::cout << i << std::endl;
            std::cout << s->getElapsedTime() << std::endl;
            ++i;
        }
        if (i == 5)
        {
            s->restart();
            i++;
        }
    }

    return 0;
}