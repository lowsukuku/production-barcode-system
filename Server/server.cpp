//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "server.h"

Server::Server(std::string serverIP, unsigned short serverPORT) : ip(serverIP), port(serverPORT){

}

void Server::start() {
    try {
        auto const address = net::ip::make_address("127.0.0.1");
        // The acceptor receives incoming connections
        tcp::acceptor acceptor{ioc, {address, port}};
        accept(std::move(acceptor));
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }
}

void Server::stop() {

}

void Server::accept(tcp::acceptor &&acceptor) {
    for (;;) {
        try {
            // This will receive the new connection
            tcp::socket socket{ioc};

            // Block until we get a connection
            acceptor.accept(socket);
            acceptor.accept(socket);

            // Launch the session, transferring ownership of the socket
            std::thread{&Server::clientHandler, this, std::move(socket)}.detach();
        }
        catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return;
        }
    }
}

void Server::clientHandler(tcp::socket &&socket) {

}

enum ClientType Server::getType(std::string helloMessage) {
    return user;
}
