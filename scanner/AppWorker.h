#pragma once

#include "HTTPClient.h"
#include "KeyboardControl.h"
#include "SelectorControl.h"
#include "TCPSocket.h"
#include "WifiController.h"

class AppWorker {
 private:
  void ConnectWifi(WifiController &controller);

 public:
  AppWorker(/* args */) {}
  ~AppWorker() {}

  void Run() {
    WifiController controller;
    ConnectWifi(controller);
    TCPSocket socket = TCPSocket(controller);
    if (socket.Connect("127.0.0.1") == false) throw("Connection failed");
    HTTPClient client = HTTPClient(socket);
    }
};