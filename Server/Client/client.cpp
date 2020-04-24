//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "client.h"

Client::Client(tcp::socket &&sock) : socket(std::move(sock)), worker(nullptr){

}

void Client::getRequest() {
    try {
        // Construct the stream by moving in the socket
        websocket::stream<tcp::socket> ws{std::move(socket)};

        // Set a decorator to change the Server of the handshake
        ws.set_option(websocket::stream_base::decorator(
                [](websocket::response_type &res) {
                    res.set(http::field::server,
                            std::string(BOOST_BEAST_VERSION_STRING) +
                            " websocket-server-sync");
                }));

        // Accept the websocket handshake
        ws.accept();

        try{
            for (;;) {
                // This buffer will hold the incoming message
                beast::flat_buffer buffer;

                // Read a message
                ws.read(buffer);

                // Echo the message back

                std::cout<<boost::beast::buffers_to_string(buffer.data())<<std::endl;
                ws.text(ws.got_text());
                ws.write(buffer.data());
            }
        }
        catch (...){
            return;
        }
    }
    catch (beast::system_error const &se) {
        // This indicates that the session was closed
        if (se.code() != websocket::error::closed)
            std::cerr << "Error: " << se.code().message() << std::endl;
    }
    catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Client::sendRequest(std::string data) {

}
