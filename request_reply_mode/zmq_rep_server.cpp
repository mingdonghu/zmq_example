//
// Hello World server in C++
// Binds REP socket to tcp://*:5555
// Expects "Hello" from client, replies with "World"
//
#include <iostream>
#include <string>
#include <zmq.hpp>

#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n) Sleep(n)
#endif

int main() {
  std::cout << "ZeroMQ Version-> major: " << std::get<0>(zmq::version()) << " "
            << "minor: " << std::get<1>(zmq::version()) << " "
            << "patch: " << std::get<2>(zmq::version()) << " "
            << std::endl;

  // Prepare our context and socket
  zmq::context_t context(1);
  zmq::socket_t socket(context, zmq::socket_type::rep);
  socket.bind("tcp://*:5555");

  while (true) {
    zmq::message_t request;

    // Wait for next request from client
    socket.recv(request, zmq::recv_flags::none);

    std::cout << "Received Hello" << std::endl;

    // Do some 'work'
    sleep(1);

    // Send reply back to client
    zmq::message_t reply(5);
    memcpy(reply.data(), "World", 5);
    socket.send(reply, zmq::send_flags::none);
  }
  return 0;
}