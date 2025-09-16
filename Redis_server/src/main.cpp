#include <iostream>
#include "../include/RedisServer.h"
#include "../include/RedisDatabase.h"
#include <thread>
#include <chrono>

using namespace std;
int main(int argc, char *argv[])
{
    int port = 6379;
    if (argc >= 2)
        port = stoi(argv[1]);

    // Creates a RedisServer object (your server class) listening on the chosen port
    if (RedisDatabase::getInstance().load("dump.my_rdb"))
        std::cout << "Database Loaded\n";
    else
        std::cout << "Failed to load database\n";
    RedisServer server(port);

    // background persistence - dump database the every 300 seconds - 5 mins - save database
    std::thread persistanceThread([]()
                                  {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(300));

            if (!RedisDatabase::getInstance().dump("dump.my_rdb"))
                std::cerr << "Error Dumping Database\n";
            else 
                std::cout << "Database Dumped to dump.my_rdb\n";
        } });
    // don’t wait for this thread to finish, let it run in the background.
    persistanceThread.detach();

    server.run();

    return 0;
}
