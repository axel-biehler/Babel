 //
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2021 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <Networking/Server.hpp>
#include <Database/Database.hpp>
#include <Networking/HandlePacket.hpp>
#include <Database/Message.hpp>

 void handle_arg(int ac, char* av[])
{
    if (ac < 2) {
        std::cerr << "Bad argument." << std::endl;
        exit(84);
    }
    try {
        std::stoi(av[1]);
    }
    catch (std::invalid_argument e) {
        std::cerr << "Bad argument." << std::endl;
        exit(84);
    }
}

#include <Networking/Server.hpp>
#include <Database/Database.hpp>
#include <Networking/HandlePacket.hpp>

 int main(int argc, char* argv[])
 {
     auto database = std::make_shared<Babel::Database::Database>("db.sqlite");
     asio::io_context context;
     auto server = std::make_shared<Babel::Networking::Server>(context, std::stoi(argv[1]), database);
     auto handlePacket = std::make_shared<Babel::Networking::HandlePacket>(server);
     server->setHandlePacket(handlePacket);
     server->async_accept();
     context.run();

     return 0;
 }