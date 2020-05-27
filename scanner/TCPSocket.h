#pragma once
#include <cstdint>

#include "WifiController.h"

struct IPAddress {
  uint8_t addressBytes[4] = {0};
};

class TCPSocket {
 private:
  IPAddress _hostAddress;
  uint16_t _hostPort = 8080;
  uint16_t _timeout;
  WifiController& _wifi;

 public:
  TCPSocket(WifiController& wifi) : _wifi(wifi) {}
  ~TCPSocket() {}
  bool Connect(IPAddress address, uint16_t port = 8080) { return true; }
  bool Connect(const std::string& address, uint16_t port = 8080) {
    return true;
  }
  bool Send(uint8_t* data, size_t size) { return true; }
  bool Receive(uint8_t* data, size_t size) { return true; }
  void SetTimeout(uint16_t timeout) { _timeout = timeout; }
};