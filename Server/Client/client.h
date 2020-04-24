//
// Created by Daniil Tchyorny on 19.04.2020.
//

#ifndef HTTPSERVER_CLIENT_H
#define HTTPSERVER_CLIENT_H
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "../HttpHandler/httphandler.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class Client {
public:
    explicit Client(tcp::socket &&sock);

    virtual void handleClient(std::string request)=0;

protected:
    void getRequest();

    void sendRequest(std::string data);

    virtual bool signIn(std::string request)=0;

protected:
    tcp::socket socket;
    HttpHandler *worker;
};


#endif //HTTPSERVER_CLIENT_H
