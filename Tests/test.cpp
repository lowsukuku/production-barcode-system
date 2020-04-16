//
// Created by Dellvin on 06.03.2020.
//
#include "gtest/gtest.h"

extern "C" {
    #include "../Server/server.h"
}

class user1{
public:
    void send(std::string);
    std::string read();
    void connect();
};

class device1{
public:
    void send(std::string);
    void connect();
};

TEST(test, Test2) {
    Server serv;
    Scaner scan;
    User usr;
    HttpHandler handle;
    Router rout;

    EXPECT_NE(usr.generateID(), usr.generateID());

    serv.start();
    EXPECT_EQ(serv.users.size(), 0);
    EXPECT_EQ(serv.devices.size(), 0);
    for(int i=0;i<100;++i){
        user1 us;
        us.connect();
    }
    EXPECT_EQ(serv.users.size(), 1);

    for(int i=0;i<100;++i){
        device1 dev;
        dev.connect();
    }
    EXPECT_EQ(serv.users.size(), 1);

    sleep(5*60);

    EXPECT_EQ(serv.users.size(), 0);
    EXPECT_EQ(serv.devices.size(), 0);

    user1 us;
    us.connect();
    us.send("qwerty");
    EXPECT_EQ( "qwerty", handle.getHTTP());

    device1 dev;
    dev.connect();
    dev.send("asdfadsf");
    EXPECT_EQ( "asdfadsf", handle.getHTTP());

}
