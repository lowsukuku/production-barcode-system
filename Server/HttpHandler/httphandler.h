//
// Created by Daniil Tchyorny on 19.04.2020.
//

#ifndef HTTPSERVER_HTTPHANDLER_H
#define HTTPSERVER_HTTPHANDLER_H

#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "../Client/Router/router.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class HttpHandler {
public:
    HttpHandler(tcp::socket &&sock);

    void parseRequest(const std::string &request);

    RequestType getRequestType(const std::string &request);

    std::string dataToRequest(const std::string &data);

    std::string getRequest();

    void sendRequest(std::string &&data);

public:
    HttpRequest request;
    tcp::socket socket;
    HttpHandler *worker;
    websocket::stream<tcp::socket> ws{std::move(socket)};
};


#endif //HTTPSERVER_HTTPHANDLER_H
