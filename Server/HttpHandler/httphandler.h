//
// Created by Daniil Tchyorny on 19.04.2020.
//

#ifndef HTTPSERVER_HTTPHANDLER_H
#define HTTPSERVER_HTTPHANDLER_H
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using namespace std;

enum RequestType{
    POST,
    GET,
};

struct HttpRequest{
    enum RequestType type;
    std::string method;
    uint64_t contentLength;
    std::string data;
};

class HttpHandler {
public:
    void parseRequest(std::string request);

    std::string getRequestType(std::string request);

    std::string dataToRequest(std::string data);

public:
    HttpRequest request;
};


#endif //HTTPSERVER_HTTPHANDLER_H
