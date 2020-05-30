//
// Created by Daniil Tchyorny on 19.04.2020.
//

#include "httphandler.h"
#include <time.h>


HttpRequest HttpHandler::parseRequest(const std::string &request) {
    HttpRequest r;
    r.typeRequest=getRequestType(request);
    if(r.typeRequest==POST){
        std::string content=getContent(request);
        r.client=getClientType(content);
        r.method=getPostMethod(content);
        r.data=content;
        r.contentLength=content.size();
    }
    else{
        r.method=getGetMethod(request);
        r.data=getGetData(request);
    }
    r.rawRequest=request;
    return r;
}

std::string HttpHandler::getGetMethod(const std::string &request) {
    uint64_t pos=request.find("contextType=");pos+=strlen("contextType=");
    std::string method;
    while(request[pos]!='&' && request[pos]!=' '){
        method+=request[pos];
        pos++;
    }
    return method;
}

std::string HttpHandler::getGetData(const std::string &request) {
    int64_t pos=request.find('&');
    if(pos==-1)return "";
    pos++;
    std::string data;
    while(request[pos]!=' ' && request[pos]!='\n'){
        data+=request[pos];
        pos++;
    }
    return std::string();
}

std::string HttpHandler::getPostMethod(const std::string &content) {
    uint64_t pos=content.find("contextType");pos+=3; pos+=strlen("contextType");
    std::string method;
    while(content[pos]!='"'){
        method+=content[pos];
        pos++;
    }
    return method;
}

enum ClientType HttpHandler::getClientType(const std::string &content) {
    if(content.find("User")) return ClientType ::USER;
    return ClientType ::SCANER;

}

std::string HttpHandler::getContent(const std::string &request){
    uint64_t pos=request.find("\"context\":{");
    std::string content;
    content+='{';
    int openedObj=1;
    while(openedObj!=0){
        if(request[pos]=='{')openedObj++;
        if(request[pos]=='}')openedObj--;
        content+=request[pos];
        pos++;
    }
    return content;
}

RequestType HttpHandler::getRequestType(const std::string &request) {
    int8_t type=request.find("POST");
    if(type==-1)return GET;
    return POST;
}

std::string HttpHandler::dataToRequest(const std::string &data) {
    std::string answer;
    bool errorFlag=false;
    if(data.find("ERROR")!=-1){
        answer+="HTTP/1.1 505 ";
        answer+=data;
        errorFlag= true;
    }
    else{
        answer+="HTTP/1.1 200 OK ";
    }

    answer+="Server: DellvinConnect";
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);
    answer+="Date:";
    answer+=asctime(timeinfo);
    if(!errorFlag)
//        answer+=data;
    return answer;
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
                            " websocket-server-dsync");
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

HttpHandler::HttpHandler(tcp::socket &&sock) : socket(std::move(sock)) {

}
