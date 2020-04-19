//
// Created by Dellvin on 06.03.2020.
//
#include "gtest/gtest.h"

#include "../Server/server.h"

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
    Server s;
    s.start();
    s.stop();
    EXPECT_EQ(true, true);
}
