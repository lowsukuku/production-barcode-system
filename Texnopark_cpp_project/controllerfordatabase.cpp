#include "controllerfordatabase.h"
#include <string>
#include <iostream>
#include <QDebug>
using namespace std;
ControllerForDataBase::ControllerForDataBase()
{

}

bool ControllerForDataBase::isAuthorized(const QString &login, const QString &password)
{
    ptree root, client;
    userLogin = login.toStdString();
    userPassword = password.toStdString();

    root.put("clientType", "User");

    client.put("login", login.toStdString());
    client.put("password", password.toStdString());
    client.put("contextType","authorization");

    root.add_child("client", client);

    std::ostringstream buf;
    write_json (buf, root, false);
    std::string json = buf.str();
    sendPostRequest("Authorization", json);
    return true;
}

bool ControllerForDataBase::addProductType(const QString &name)
{
    ptree root, client, context;
    context.put ("modelName", name.toStdString());

    client.put("login", userLogin);
    client.put("password", userPassword);
    client.put("contextType","AddModel");
    client.add_child("context", context);

    root.put("clientType", "User");
    root.add_child("client", client);

    std::ostringstream buf;
    write_json (buf, root, false);
    std::string json = buf.str();
    sendPostRequest("addProductType", json);
    return true;
}

QStringList ControllerForDataBase::addProduct(const QString &productType, const QString &amount)
{
    qDebug()<<"add Product\n\n\n\n\n";
    ptree root, client, context;
    context.put ("modelName", productType.toStdString());
    context.put ( "amount", amount.toStdString());

    client.put("login", userLogin);
    client.put("password", userPassword);
    client.put("contextType","AddDevice");
    client.add_child("context", context);

    root.put("clientType", "User");
    root.add_child("client", client);


    std::ostringstream buf;
    write_json (buf, root, false);
    std::string json = buf.str();
    sendPostRequest("addProducts", json);
    return {"1","2", "3"};
}


ProductHistory ControllerForDataBase::getProductHistory(const QString &productType, const QString &id)
{
    ptree jsonTree = sendGetRequest("getProductHistory/"+productType.toStdString()+"/"+id.toStdString());
    return {productType, id, "добавление", "сборка", "регулировка", "отк", "отгрузка"};
}


QList<Product> ControllerForDataBase::getProductsByType(const QString &productType)
{
    ptree jsonTree = sendGetRequest("getProductsByType/"+productType.toStdString());
    QList<Product> list;
    for(int i=0; i<5; ++i){
        QString tmp = QString::number(i);
        list.push_back({productType, "дата"+tmp, "id"+tmp,"state"+tmp});
    }
    return list;
}



QList<ProductType> ControllerForDataBase::getAllProductsType()
{
    ptree jsonTree = sendGetRequest("/?contextType=GetAllModels");
    QList<ProductType> list;
    for(int i=0; i<5; ++i){
        QString tmp = QString::number(i);
        list.push_back({"модель"+tmp, "дата"+tmp, "всего"+tmp,"собрано"+tmp, "настроено"+tmp,"отк"+tmp,"отгружено"+tmp });
    }
    return list;
}

QStringList ControllerForDataBase::getIdByType(const QString &productType)
{
    ptree jsonTree = sendGetRequest("getIdByType/"+productType.toStdString());
    return {"id0","id1","id2","id3"};
}

QStringList ControllerForDataBase::getTypesList()
{
    ptree jsonTree = sendGetRequest("getTypesList");
    return {"модель0","модель1","модель2", "модель3" };
}



QList<Product> ControllerForDataBase::getAllProducts()
{
    ptree jsonTree = sendGetRequest("/?contextType=GetAllDevices");

    QList<Product> list;
    for(int i=0; i<5; ++i){
        QString tmp = QString::number(i);
        list.push_back({"модель"+tmp, "дата"+tmp, "id"+tmp,"state"+tmp});
    }
    return list;
}

boost::property_tree::ptree ControllerForDataBase::sendGetRequest(string target)
{

    ptree res;
    string host = "127.0.0.1";
    try{
    // Get a list of endpoints corresponding to the server name.
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::endpoint ep( boost::asio::ip::address::from_string(host), 80);    // Try each endpoint until we successfully establish a connection.
    tcp::socket socket(io_service);
    socket.connect(ep);

    // Form the request. We specify the "Connection: close" header so that the
    // server will close the socket after transmitting the response. This will
    // allow us to treat all data up until the EOF as the content.
    boost::asio::streambuf request;
    std::ostream request_stream(&request);
    request_stream << "GET " << target << " HTTP/1.0\r\n";
    request_stream << "Host: " << "127.0.0.1" << "\r\n";
    request_stream << "Accept: */*\r\n";
    request_stream << "Connection: close\r\n\r\n";
    // Send the request.
    boost::asio::write(socket, request);

    // Read the response status line. The response streambuf will automatically
    // grow to accommodate the entire line. The growth may be limited by passing
    // a maximum size to the streambuf constructor.
    boost::asio::streambuf response;
    boost::asio::read_until(socket, response, "\r\n");

    // Check that response is OK.
    std::istream response_stream(&response);
    std::string http_version;
    response_stream >> http_version;
    unsigned int status_code;
    response_stream >> status_code;
    std::string status_message;
    std::getline(response_stream, status_message);
    bool flag = true;
    if (!response_stream || http_version.substr(0, 5) != "HTTP/")
    {
        qDebug() << "Invalid response\n";
        flag =  false;
    }
    if (status_code != 200)
    {
        qDebug() << "Response returned with status code " << status_code << "\n";
        flag =  false;
    }

    // Read the response headers, which are terminated by a blank line.
    boost::asio::read_until(socket, response, "\r\n\r\n");

    // Process the response headers.
    std::string header;
    while (std::getline(response_stream, header) && header != "\r")
        qDebug() << QString::fromStdString(header) << "\n";
    qDebug() << "\n";

    // Write whatever content we already have to output.
    if (response.size() > 0)
        qDebug() << &response;

    // Read until EOF, writing data to output as we go.
    boost::system::error_code error;
    while (boost::asio::read(socket, response,
                             boost::asio::transfer_at_least(1), error))
        qDebug() << &response;
    if (error != boost::asio::error::eof)
        flag =  false;

    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    }
    catch(...){
        qDebug()<<"something going wrong get\n";
    }

    return res;
}

ptree ControllerForDataBase::sendPostRequest(string target, string json)
{
    ptree res;
    try{
        string host = "127.0.0.1";
        // Get a list of endpoints corresponding to the server name.
        boost::asio::io_service service;
        boost::asio::ip::tcp::endpoint ep( boost::asio::ip::address::from_string("127.0.0.1"), 80);    // Try each endpoint until we successfully establish a connection.
        tcp::socket socket(service);
        socket.connect(ep);
        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        boost::asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "POST "+target+" HTTP/1.1 \r\n";
        request_stream << "Host:" << host << "\r\n";
        request_stream << "User-Agent: C/1.0\r\n";
        request_stream << "Content-Type: application/json; charset=utf-8 \r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Content-Length: " << json.length() << "\r\n";
        request_stream << "Connection: close\r\n\r\n";  //NOTE THE Double line feed
        request_stream << json;
        // Send the request.
        boost::asio::write(socket, request);

        // Read the response status line. The response streambuf will automatically
        // grow to accommodate the entire line. The growth may be limited by passing
        // a maximum size to the streambuf constructor.
        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");
        // Check that response is OK.
        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);
        bool flag = true;
        if (!response_stream || http_version.substr(0, 5) != "HTTP/")
        {
            qDebug() << "Invalid response\n";
            flag =  false;
        }
        if (status_code != 200)
        {
            qDebug() << "Response returned with status code " << status_code << "\n";
            flag =  false;
        }

        // Read the response headers, which are terminated by a blank line.
        boost::asio::read_until(socket, response, "\r\n\r\n");

        // Process the response headers.
        std::string header;
        while (std::getline(response_stream, header) && header != "\r")
            qDebug() << QString::fromStdString(header) << "\n";
        qDebug() << "\n";

        // Write whatever content we already have to output.
        if (response.size() > 0)
            qDebug() << &response;

        // Read until EOF, writing data to output as we go.
        boost::system::error_code error;
        while (boost::asio::read(socket, response,
                                 boost::asio::transfer_at_least(1), error))
            qDebug() << &response;
        if (error != boost::asio::error::eof)
            flag =  false;

        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    }
    catch (...) {
        qDebug()<<"something going wrongPost\n";
    }
    return res;
}
