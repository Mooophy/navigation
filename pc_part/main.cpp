#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unistd.h>
#include "sample.hpp"
#include "queue.hpp"

int main()
{
    //! build bluetooth stream.
    std::string     raw_data;
    std::fstream    blueTooth("/dev/rfcomm0");

    navigation::Queue data(10);
    while(blueTooth >> raw_data)
    {
        std::cout << "raw : " <<raw_data << std::endl;
        navigation::sample smp(raw_data);
        std::cout << "smp : " << smp.result() << std::endl;

        data << smp.result();

        std::cout << "direction suggest: " << data.suggest() << std::endl;
    }
}
