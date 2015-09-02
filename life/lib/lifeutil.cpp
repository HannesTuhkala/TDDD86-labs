#include <cstdlib>
#include <chrono>
#include <thread>
#include "lifeutil.h"

void clearConsole()
{
#if defined(_WIN32) || defined (_WIN64)
        std::system("CLS");
#else
        // assume POSIX
        std::system("clear");
#endif
}


void pause(int ms)
{
    if (ms > 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
}
