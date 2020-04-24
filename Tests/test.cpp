//
// Created by Dellvin on 06.03.2020.
//
#include "gtest/gtest.h"

#include "../Server/server.h"

class device : public Scaner{
public:
    device(){
    }
    void send(std::string text){
        ws.write(net::buffer(std::string(text)));
    }
    std::string read(){
        // This buffer will hold the incoming message
        beast::flat_buffer buffer;
        // Read a message into our buffer
        ws.read(buffer);
        return boost::beast::buffers_to_string(buffer.data());
    }
    void connect(){
        auto const host = "127.0.0.1"; // "echo.websocket.org";
        auto const port = "3000";

        // The io_context is required for all I/O


        // These objects perform our I/O
        tcp::resolver resolver{ioc};

        // Look up the domain name
        auto const results = resolver.resolve(host, port);

        // Make the connection on the IP address we get from a lookup
        net::connect(ws.next_layer(), results.begin(), results.end());

        ws.set_option(websocket::stream_base::decorator([](websocket::response_type &req) {
            req.set(http::field::user_agent,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                    " websocket-client-coro");
        }));

        // Perform the websocket handshake
        ws.handshake(host, "/");
    }

    void close(){
        // Close the WebSocket connection
        ws.close(websocket::close_code::normal);
    }

private:
    net::io_context ioc;
    websocket::stream<tcp::socket> ws{ioc};
};

class user : public User{
public:
    user()= default;
    void send(std::string text){
        ws.write(net::buffer(std::string(text)));
    }
    std::string read(){
        // This buffer will hold the incoming message
        beast::flat_buffer buffer;
        // Read a message into our buffer
        ws.read(buffer);
        return boost::beast::buffers_to_string(buffer.data());
    }
    void connect(){
        auto const host = "127.0.0.1"; // "echo.websocket.org";
        auto const port = "3000";

        // The io_context is required for all I/O


        // These objects perform our I/O
        tcp::resolver resolver{ioc};

        // Look up the domain name
        auto const results = resolver.resolve(host, port);

        // Make the connection on the IP address we get from a lookup
        net::connect(ws.next_layer(), results.begin(), results.end());

        ws.set_option(websocket::stream_base::decorator([](websocket::response_type &req) {
            req.set(http::field::user_agent,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                    " websocket-client-coro");
        }));

        // Perform the websocket handshake
        ws.handshake(host, "/");
    }

    void close(){
        // Close the WebSocket connection
        ws.close(websocket::close_code::normal);
    }

private:
    net::io_context ioc;
    websocket::stream<tcp::socket> ws{ioc};
};

TEST(test, Test2) {
    Server s();
    s().start();
    device d;
    d.connect();
    std::string message="POST/HTTP/1.1\nContent-Type: application/json\nContent-Length: 133\nHost: 127.0.0.1:8000\n{""clientType"":""Scanner"",""client"":{""apiKey"":2010345719727824955,""deviceID"":186582329519439120,""role"":""Mounting"",""utcTime"":1587150123}}";
    d.send(message);
    EXPECT_EQ("HTTP/1.1 200 OK\nContent-Length: 0\nServer: Microsoft-HTTPAPI/2.0\nDate: Fri, 17 Apr 2020 19:02:03 GMT\n", d.read());
    d.close();

    user u;
    u.connect();
    message="POST / HTTP/1.1\nContent-Type: application/json\nContent-Length: 156\nHost: 127.0.0.1:8000\n{""clientType"":""User"",""client"":{""login"":""mRj9wpsFny"",""password"":""K6S1uKxP"",""contextType"":""AddDevice"",""context"":{""modelId"":3,""deviceID"":1861559598230240184}}}";
    u.send(message);
    EXPECT_EQ("HTTP/1.1 200 OK\nContent-Length: 0\nServer: Microsoft-HTTPAPI/2.0\nDate: Fri, 17 Apr 2020 19:02:03 GMT\n", u.read());
    u.close();

    u.connect();
    message="POST / HTTP/1.1\nContent-Type: application/json\nContent-Length: 156\nHost: 127.0.0.1:8000\n{""clientType"":""User"",""client"":{""login"":""mRj9wpsFny"",""password"":""K6S1uKxP"",""contextType"":""AddModel"",""context"":{""modelName"":""Model 42""}}}";
    u.send(message);
    EXPECT_EQ("HTTP/1.1 200 OK\nContent-Length: 0\nServer: Microsoft-HTTPAPI/2.0\nDate: Fri, 17 Apr 2020 19:02:03 GMT\n", u.read());
    u.close();

    u.connect();
    message="POST / HTTP/1.1\nContent-Type: application/json\nContent-Length: 156\nHost: 127.0.0.1:8000\n{""clientType"":""User"",""client"":{""login"":""mRj9wpsFny"",""password"":""K6S1uKxP"",""contextType"":""DeleteModel"",""context"":{""modelName"":""Model 42""}}}";
    u.send(message);
    EXPECT_EQ("HTTP/1.1 200 OK\nContent-Length: 0\nServer: Microsoft-HTTPAPI/2.0\nDate: Fri, 17 Apr 2020 19:02:03 GMT\n", u.read());
    u.close();

    message="GET /?contextType=GetDeviceById&id=1478668906952015500 HTTP/1.1\nHost: 127.0.0.1:8000";
    u.send(message);
    EXPECT_EQ("HTTP/1.1 200 OK\nContent-Length: 0\nServer: Microsoft-HTTPAPI/2.0\nDate: Fri, 17 Apr 2020 19:02:03 GMT\n", u.read());
    u.close();

    message="GET /?contextType=GenerateUniqueID HTTP/1.1\nHost: 127.0.0.1:8000";
    u.send(message);
    EXPECT_EQ("HTTP/1.1 200 OK\nContent-Length: 18\nServer: Microsoft-HTTPAPI/2.0\nDate: Fri, 17 Apr 2020 19:02:03 GMT\n172168591419290202\n", u.read());
    u.close();

    s().stop();

    EXPECT_EQ(true, true);
}
