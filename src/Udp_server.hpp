#pragma once
#include <boost/asio.hpp>
#include <string>
#include <vector>

using boost::asio::ip::udp;

class Udp_server {
public:

  Udp_server(boost::asio::io_service& io_service, const std::string& host, const std::string& port) :
  io_service_(io_service),
  socket_(io_service, udp::endpoint(udp::v4(), 8080)) {
    udp::resolver resolver(io_service_);
    udp::resolver::query query(udp::v4(), host, port);
    udp::resolver::iterator iter = resolver.resolve(query);
    remote_endpoint_ = *iter;
    }

    ~Udp_server() {
      socket_.close();
    }


  void send(const std::string& msg) {
    socket_.send_to(boost::asio::buffer(msg, msg.size()), remote_endpoint_);
  }

  void receive(std::string& msg) {
    socket_.receive_from(boost::asio::buffer(msg, msg.size()), remote_endpoint_);
  }


private:
  boost::asio::io_service& io_service_;
  udp::socket socket_;
  udp::endpoint remote_endpoint_;
  std::vector<char> recv_buffer_;

};