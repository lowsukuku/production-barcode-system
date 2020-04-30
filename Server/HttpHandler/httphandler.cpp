//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "httphandler.h"

void HttpHandler::parseRequest(const std::string &request) {

}

RequestType HttpHandler::getRequestType(const std::string &request) {
    return POST;
}

std::string HttpHandler::dataToRequest(const std::string &data) {
    return std::string();
}

std::string HttpHandler::getRequest() {
    beast::flat_buffer buffer;
    try {
        // Construct the stream by moving in the socket


        // Set a decorator to change the Server of the handshake
        ws.set_option(websocket::stream_base::decorator(
                [](websocket::response_type &res) {
                    res.set(http::field::server,
                            std::string(BOOST_BEAST_VERSION_STRING) +
                            " websocket-server-sync");
                }));

        // Accept the websocket handshake

        ws.accept();

        try {
            // This buffer will hold the incoming message


            // Read a message
            ws.read(buffer);

            // Echo the message back

            std::cout << boost::beast::buffers_to_string(buffer.data()) << std::endl;

        }
        catch (...) {
            return "";
        }
    }
    catch (beast::system_error const &se) {
        // This indicates that the session was closed
        if (se.code() != websocket::error::closed)
            std::cerr << "Error: " << se.code().message() << std::endl;
        return "";
    }
    catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return "";
    }
    return boost::beast::buffers_to_string(buffer.data());
}

void HttpHandler::sendRequest(std::string &&data) {
    std::string s = data;
    auto buffer = boost::asio::dynamic_buffer(s);
    ws.text(ws.got_text());
    ws.write(buffer.data());
    ws.close(websocket::close_code::normal);
}

HttpHandler::HttpHandler(tcp::socket &&sock) : socket(std::move(sock)), worker(nullptr) {

}