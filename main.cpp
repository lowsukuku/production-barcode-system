#include <iostream>
#include "./Server/server.h"

int main() {



    Server s("192.168.204.129");



    s.start();
    return 0;
}
