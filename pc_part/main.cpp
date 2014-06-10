#include <iostream>
#include <string>
#include <unistd.h>
#include "sample.hpp"
#include "queue.hpp"
#include "data.hpp"
#include <thread>

namespace navigation {
void play( std::size_t* direction )
{
    while(true)
    {
        switch(*direction)
        {
        case 4:     system("play back.wav");    break;
        case 1:     system("play left.wav");     break;
        case 2:     system("play middle.wav");   break;
        case 3:     system("play right.wav");    break;
        }
    }
}
}//namespace

int main()
{
    std::fstream blueTooth("/dev/rfcomm0");
    navigation::data data(10);

    std::size_t direction = 0;
    std::thread back_ground(navigation::play, &direction);

    std::string raw_data;
    while(blueTooth >> raw_data)
    {
        data.insert(raw_data);

        direction = data.suggest();

        std::cout   << "\nraw : "
                    << "\033[1;31m"
                    << raw_data
                    << "\033[0m\n";

        std::cout   << "direction suggest: "
                    << "\033[1;32m"
                    << data.suggest()
                    << "\033[0m\n";
    }

    back_ground.join();




//    std::fstream blueTooth("/dev/rfcomm0");
//    std::size_t direction = 0;

//    std::thread back_ground(navigation::play, &direction);

//    navigation::Queue data(10);
//    std::string raw_data;
//    while(blueTooth >> raw_data)
//    {
//        navigation::sample smp(raw_data);
//        data << smp.result();

//        direction = data.suggest();

//        std::cout   << "\nraw : "
//                    << "\033[1;31m"
//                    << raw_data
//                    << "\033[0m\n";

//        std::cout   << "smp : "
//                    << "\033[1;33m"
//                    << smp.result()
//                    << "\033[0m\n";

//        std::cout   << "direction suggest: "
//                    << "\033[1;32m"
//                    << data.suggest()
//                    << "\033[0m\n";
//    }

//    back_ground.join();
}
