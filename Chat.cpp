//===- Chat.cpp - The main driver for a sockets chat application.-*- C++ -*-===//
//
//                          Francisco Aguilera
//
//===-----------------------------------------------------------------------===//
///
/// \file
/// This file contains the main driver for the ChatClient, ChatServer,
/// and ChatSystem classes.
///
//===-----------------------------------------------------------------------===//

#include <iostream> // cout, cerr, endl...
#include <memory>   // unique_ptr
#include <cstdlib>  // EXIT_FAILURE, EXIT_SUCCESS

#include "chat/ChatClient.hpp"
#include "chat/ChatServer.hpp"
#include "chat/EAIException.hpp"
#include "chat/SystemException.hpp"

void printUsage(std::string ExeName) {
  std::cout << "Usage: " << ExeName << " [-h] -p port -s ip" << std::endl;
}

void InteractionLoop(ChatSystem *System, std::string &MessageBuffer) {
  try {
    while (true) {
      std::cout << "You: ";
      std::getline(std::cin, MessageBuffer);
      System->sendMessage(MessageBuffer);
      std::cout << "Friend: " << System->receiveMessage() << std::endl;
    }
  } catch (const SystemException &Exception) {
    std::cerr << Exception.what() << std::endl;
  } catch (const std::invalid_argument &Exception) {
    std::cerr << Exception.what() << std::endl;
    InteractionLoop(System, MessageBuffer);
  }
}

int main(int argc, char *argv[]) {
  std::string MessageBuffer;
  switch (argc) {
  case 1: {
    std::unique_ptr<ChatServer> Server = std::make_unique<ChatServer>();
    ChatSystem *System = (ChatSystem *)Server.get();
    std::cout << "Welcome to Chat!" << std::endl;
    std::cout << "Waiting for a connection on " << Server->getIP() << " port "
              << Server->getPort() << std::endl;
    Server->listen();
    std::cout << "Found a friend! You receive first." << std::endl;
    std::cout << "Friend: " << System->receiveMessage() << std::endl;
    InteractionLoop(System, MessageBuffer);
    break;
  }
  case 5: {
    std::string FirstArg(argv[1]);
    std::string SecondArg(argv[3]);
    std::string PortValue;
    std::string IPValue;

    if ("-p" == FirstArg && "-s" == SecondArg) {
      PortValue = argv[2];
      IPValue = argv[4];
    } else {
      if ("-s" == FirstArg && "-p" == SecondArg) {
        PortValue = argv[4];
        IPValue = argv[2];
      } else {
        printUsage(argv[0]);
        return EXIT_FAILURE;
      }
    }

    std::cout << "Connecting to server..." << std::endl;
    std::unique_ptr<ChatClient> Client =
        std::make_unique<ChatClient>(PortValue, IPValue);
    ChatSystem *System = (ChatSystem *)Client.get();
    std::cout << "Connected!" << std::endl;
    std::cout << "Connected to a friend! You send first." << std::endl;
    InteractionLoop(System, MessageBuffer);
    break;
  }
  case 2:
  default:
    printUsage(argv[0]);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}