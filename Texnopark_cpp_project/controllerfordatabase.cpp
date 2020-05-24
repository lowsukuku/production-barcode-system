#include "controllerfordatabase.h"
#include <string>
#include <iostream>
#include <QDebug>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <sstream>
#include <QErrorMessage>
namespace http = boost::beast::http;
using boost::property_tree::ptree; using boost::property_tree::read_json; using boost::property_tree::write_json;
using boost::asio::ip::tcp;
using namespace std;
ControllerForDataBase::ControllerForDataBase()
{

}

bool ControllerForDataBase::isAuthorized(const QString &login, const QString &password)
{
    bool res = false;
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
    ptree jsonTree = sendPostRequest("/", json);

    if(!jsonTree.empty()){
        try {
            res = jsonTree.get<string>("context.result")=="ok";
        }
        catch (...) {
            qDebug()<<"can not authorizate";
        }
    }
    return res;
}

bool ControllerForDataBase::addProductType(const QString &name)
{
    ptree root, client, context;
    bool res = false;
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
    ptree jsonTree = sendPostRequest("/", json);

    if(!jsonTree.empty()){
        try{
             res = jsonTree.get<string>("context.result")=="ok";
        }
        catch(...){}
    }

    return res;
}

QStringList ControllerForDataBase::addProduct(const QString &productType, const QString &amount)
{
    qDebug()<<"add Product\n\n\n\n\n ";
    QStringList res;
    for(int i=0; i<amount.toInt(); ++i){
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
        write_json (buf, root);
        std::string json = buf.str();
        ptree jsonTree = sendPostRequest("/", json);

        stringstream stream;
        write_json(stream, jsonTree);
        qDebug()<<"\n\njson tree "<<stream.str().c_str();
        if(!jsonTree.empty()){
            try{
                res.append(QString(jsonTree.get<string>("context.deviceId").c_str()));
            }
            catch(...){

            }
        }
    }
    return res;
}


ProductHistory ControllerForDataBase::getProductHistory(const QString &productType, const QString &id)
{

    ProductHistory res;
    ptree jsonTree = sendGetRequest("/?contextType=getDeviseHistory&model="+productType.toStdString()+"&id="+id.toStdString());
    if(!jsonTree.empty()){
        try{
            res.id = QString(jsonTree.get<string>("context.deviceId").c_str());
            res.dateOfAdd = QString(jsonTree.get<string>("context.creationUtc").c_str());
            res.dateOfBuild = QString(jsonTree.get<string>("context.mountingUtc").c_str());
            res.dateOfAdjustment = QString(jsonTree.get<string>("context.tuningingUtc").c_str());
            res.dateOfOtk = QString(jsonTree.get<string>("context.qualityCheckUtc").c_str());
            res.dateOfShipping = QString(jsonTree.get<string>("context.shipmentUtc").c_str());
        }
        catch(...){}

    }
    return res;
}


QList<Product> ControllerForDataBase::getProductsByType(const QString &productType)
{
    ptree jsonTree = sendGetRequest("/?contextType=getDevisesByModel&model="+productType.toStdString());
    QList<Product> list;
    if(!jsonTree.empty()){
        try{
            ptree arr = jsonTree.get_child("context");
            for(auto iter: arr){
                QString id = QString(iter.second.get<string>("deviceId").c_str());
                QString type = QString(iter.second.get<string>("modelId").c_str());
                QString date = QString(iter.second.get<string>("creationUtc").c_str());
                QString state = "добавлено";

                if(iter.second.get<bool>("mountingPassed")){
                    state = "собрано";
                }
                if(iter.second.get<bool>("tuningPassed")){
                    state = "прошло регулировку";
                }
                if(iter.second.get<bool>("qualityCheckPassed")){
                    state = "прошло ОТК";
                }
                if(iter.second.get<bool>("shipmentPassed")){
                    state = "прошло ОТК";
                }
                list.push_back({type, date, id, state});
            }

        }
        catch(...){}
    }
    return list;
}



QList<ProductType> ControllerForDataBase::getAllProductsType()
{
    ptree jsonTree = sendGetRequest("/?contextType=getAllModels");
    QList<ProductType> list;
    if(!jsonTree.empty()){
        try{
            ptree arr = jsonTree.get_child("context");
            for(auto iter: arr){
                ProductType p;
                p.name = QString(iter.second.get<string>("modelId").c_str());
                p.date = QString(iter.second.get<string>("creationUtc").c_str());
                p.amount = QString(iter.second.get<string>("amount").c_str());
                p.amountOfBuildsProduct = QString(iter.second.get<string>("amountOfBuildingsProduct").c_str());
                p.amountOfSettingProduct = QString(iter.second.get<string>("amountOfSettingProduct").c_str());
                p.amountAfterOtk = QString(iter.second.get<string>("amountAfterOtk").c_str());
                p.amountOfShippedProduct = QString(iter.second.get<string>("amountOfShippedProduct").c_str());
                list.push_back(p);
            }
        }
        catch(...){}
    }
    return list;
}

QStringList ControllerForDataBase::getIdByType(const QString &productType)
{
    ptree jsonTree = sendGetRequest("/?contextType=getDevisesIdByModel&model="+productType.toStdString());
    QStringList res;
    if(!jsonTree.empty()){
        try{
            ptree arr = jsonTree.get_child("context");
            for(auto iter: arr){
                res.append(QString(jsonTree.get<string>("").c_str()));
            }
        }
        catch(...){}
    }
    return res;
}

QStringList ControllerForDataBase::getTypesList()
{
    ptree jsonTree = sendGetRequest("/?contextType=getModelsList");
    QStringList res;
    if(!jsonTree.empty()){
        try{
            ptree arr = jsonTree.get_child("context");
            for(auto iter: arr){
                res.append(QString(jsonTree.get<string>("").c_str()));
            }
        }
        catch(...){}
    }
    return res;
}



QList<Product> ControllerForDataBase::getAllProducts()
{
    ptree jsonTree = sendGetRequest("/?contextType=getAllDevices");
    QList<Product> list;
    if(!jsonTree.empty()){
        try{
            ptree arr = jsonTree.get_child("context");
            for(auto iter: arr){
                QString id = QString(iter.second.get<string>("deviceId").c_str());
                QString type = QString(iter.second.get<string>("modelId").c_str());
                QString date = QString(iter.second.get<string>("creationUtc").c_str());
                QString state = "добавлено";

                if(iter.second.get<bool>("mountingPassed")){
                    state = "собрано";
                }
                if(iter.second.get<bool>("tuningPassed")){
                    state = "прошло регулировку";
                }
                if(iter.second.get<bool>("qualityCheckPassed")){
                    state = "прошло ОТК";
                }
                if(iter.second.get<bool>("shipmentPassed")){
                    state = "прошло ОТК";
                }
                list.push_back({type, date, id, state});
            }
        }
        catch(...){}
    }

    return list;
}

boost::property_tree::ptree ControllerForDataBase::sendGetRequest(string target)
{

    ptree res;
    string host = "127.0.0.1";
    std::stringstream str;

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
        if (response.size() > 0){
            str<<&response;
            // qDebug() << &response;
        }

        // Read until EOF, writing data to output as we go.
        boost::system::error_code error;
        while (boost::asio::read(socket, response,
                                 boost::asio::transfer_at_least(1), error)){
            str<<&response;
            // qDebug() << &response;
        }
        if (error != boost::asio::error::eof)
            flag =  false;

        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);

        try{
            read_json(str, res);
        }
        catch(...){
            qDebug()<<"cant read json \n";
        }
    }
    catch(...){
        qDebug()<<"something going wrong get\n";
    }
    qDebug()<<"body"<<str.str().c_str()<<"\n\n";
    return res;
}

ptree ControllerForDataBase::sendPostRequest(string target, string json)
{
    ptree res;
    std::stringstream str;
    string host = "127.0.0.1";
    try{
        // Get a list of endpoints corresponding to the server name.
        boost::asio::io_service service;
        boost::asio::ip::tcp::endpoint ep( boost::asio::ip::address::from_string(host), 80);    // Try each endpoint until we successfully establish a connection.
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
        if (response.size() > 0){
            str<<&response;
            // qDebug() << &response;
        }
        // Read until EOF, writing data to output as we go.
        boost::system::error_code error;
        while (boost::asio::read(socket, response,
                                 boost::asio::transfer_at_least(1), error)){
            str<<&response;
            // qDebug() << &response;
        }
        if (error != boost::asio::error::eof)
            flag =  false;

        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        try{
            read_json(str, res);
        }
        catch(...){
            qDebug()<<"cant read json \n";
        }
    }
    catch (...) {
        qDebug()<<"something going wrongPost\n";
    }
    qDebug()<<"body"<<str.str().c_str()<<"\n\n";
    return res;
}
