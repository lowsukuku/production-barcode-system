#pragma once

#include <string>

#include "TCPSocket.h"

class HTTPClient {
 private:
  TCPSocket &_socket;
  std::string _apiKey = "";

 public:
  HTTPClient(TCPSocket &socket, const std::string &apiKey = "")
      : _socket(socket), _apiKey(apiKey) {}
  ~HTTPClient() {}

  uint8_t Post(const std::string &request, std::string &responce) {
    return 200;
  }
};