//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "server.h"

Server::Server(std::string &&serverIP, unsigned short &&serverPORT) : ip(serverIP), port(serverPORT){
    std::cout<<"Ready!"<<std::endl;
}

void Server::start() {
    try {
        auto const address = net::ip::make_address(ip);
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
    try{
        std::cout<<"Connected!"<<std::endl;
        HttpHandler handler(std::move(socket));
        std::string request =handler.getRequest();
        HttpRequest req=handler.parseRequest(request);
        std::string answer;
        if(req.client==USER){
            UserServer user;
            answer=user.handleClient(req);
        }
        if(req.client==SCANER){
            Scaner device;
            answer=device.handleClient(req);
        }
        answer=handler.dataToRequest(answer);

        std::cout<<std::endl<<std::endl<<"Sended!"<<std::endl
                 <<answer<<std::endl;
        handler.sendRequest(std::move(answer));
    }  catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }

}
