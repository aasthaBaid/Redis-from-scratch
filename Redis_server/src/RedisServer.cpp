#include "../include/RedisServer.h"
#include "../include/RedisCommandHandler.h"
#include "../include/RedisDatabase.h"

#include <iostream>
#include <sys/socket.h> //socket functions (socket, bind, listen, accept).
#include <unistd.h>     //close() for sockets, low-level OS functions.
#include <netinet/in.h> //defines sockaddr_in (IP/port structure).
#include <vector>
#include <thread>
#include <cstring>  //memset, string operations.
#include <signal.h> //signal handling (graceful shutdown with Ctrl+C).

static RedisServer *globalServer = nullptr; // Used if you later install signal handlers (e.g., on SIGINT) so you can call globalServer->shutdown() when Ctrl+C is pressed.

void signalHandler(int signum)
{
    if (globalServer)
    {
        std::cout << "Caught Signal " << signum << ",Shutting down..\n";
        globalServer->shutdown();
    }
    exit(signum);
}

void RedisServer::setupSignalHandler()
{
    signal(SIGINT, signalHandler);
}

RedisServer::RedisServer(int port) : port(port), server_socket(-1), running(true)
{
    globalServer = this;
    setupSignalHandler();
}

void RedisServer::shutdown()
{
    running = false;
    if (server_socket != -1)
    {
        if (RedisDatabase::getInstance().dump("dump.my_rdb"))
            std::cout << "Database Loaded\n";
        else
            std::cout << "Failed to load database\n";
        close(server_socket);
    }
    std::cout << "Server shutdown complete!\n";
}

void RedisServer::run()
{
    server_socket = socket(AF_INET, SOCK_STREAM, 0); // creates a TCP socket : AF_INET = IPv4, SOCK_STREAM = TCP (stream-oriented, reliable), 0 = use default protocol (TCP here)
    if (server_socket < 0)
    {
        std::cerr << "Error Creating server socket\n";
        return;
    }
    int opt = 1;
    // SO_REUSEADDR - restart your server on the same port without waiting for TIME_WAIT sockets to expire.
    // server_Socket - file descriptor (int) returned from socket()
    // SOL_SOCKET means “socket-level options” (not TCP/IP–specific), Examples of this level: SO_REUSEADDR,  SO_KEEPALIVE, SO_RCVBUF(receive buffer size)
    // opt- pointer to option value - 1 : ON, 0: OFF
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    /**
    struct sockaddr_in {
        sa_family_t    sin_family;   // address family (AF_INET for IPv4)
        in_port_t      sin_port;     // port number (network byte order)
        struct in_addr sin_addr;     // IP address
        unsigned char  sin_zero[8];  // padding (unused)
    };
     **/
    sockaddr_in serverAddr{}; // struct defined in <netinet/in.h> that represents an IPv4 socket address.
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);       // convert port to network byte order (big endian).
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP

    // attaches the socket to the given port on this machine.
    if (bind(server_socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Error Binding server Socket\n";
        return;
    }

    // Marks socket as listening for incoming connections.
    if (listen(server_socket, 10) < 0)
    {
        std::cerr << "Error Listening to port\n";
        return;
    }

    std::cout << "Redis server listening on port :" << port << "\n";
    std::vector<std::thread> threads;

    RedisCommandHandler cmdHandler;
    while (running)
    {
        int client_socket = accept(server_socket, nullptr, nullptr); // accept() blocks until a client connects.
        if (client_socket < 0)
        {
            if (running)
            {
                std::cerr << "Error accepting client connection\n";
            }
            break;
        }
        threads.emplace_back([client_socket, &cmdHandler]()
                             {
            char buffer[1024];
            while (true) {
                memset(buffer, 0, sizeof(buffer)); // Allocate a buffer.
                int bytes = recv(client_socket, buffer, sizeof(buffer) - 1, 0); // recv() = read data from client.
                
                if (bytes <= 0)
                    break; // If bytes <= 0, client disconnected → break.
                std::string request(buffer, bytes);
                std::string response = cmdHandler.processCommand(request);
                send(client_socket, response.c_str(), response.size(), 0);
            }
            close(client_socket); });
    }
    for (auto &t : threads)
    {
        if (t.joinable())
            t.join(); // make test join us
    }
    // for shutdown
    // before shutdown , persist the database
    if (RedisDatabase::getInstance().dump("dump.my_rdb"))
        std::cout << "Database Dumped to dump.my_rdb\n";
    else
        std::cout << "Error dumping database\n";
}