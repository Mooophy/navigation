#include <iostream>
#include <string>
#include <unistd.h>
#include "sample.hpp"
#include "queue.hpp"
#include <thread>

namespace navigation {
void play( std::size_t* direction )
{
    while(true)
    {
        switch(*direction)
        {
        case 0:     system("play wrong.wav");    break;
        case 1:     system("play left.wav");     break;
        case 2:     system("play middle.wav");   break;
        case 3:     system("play right.wav");    break;
        }
    }
}
}

int main()
{
    std::fstream blueTooth("/dev/rfcomm0");
    std::size_t direction = 0;

    std::thread back_ground(navigation::play, &direction);

    navigation::Queue data(20);
    std::string raw_data;
    while(blueTooth >> raw_data)
    {
        navigation::sample smp(raw_data);
        data << smp.result();

        direction = data.suggest();

        std::cout << "\nraw : " <<raw_data << std::endl;
        std::cout << "smp : " << smp.result() << std::endl;
        std::cout << "direction suggest: " << data.suggest() << std::endl;
    }

    back_ground.join();
}
