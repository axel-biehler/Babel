#include <QApplication>
#include <Ui/ConnectionWindow/ConnectionWindow.hpp>
#include <Networking/Client.hpp>
#include <Networking/ClientUdp.hpp>
#include <iostream>

int main(int ac, char **av)
{
    QApplication app(ac, av);
    Babel::Networking::Client cli;
    Babel::Ui::ConnectionWindow connWindow(&cli);
    if (ac < 3) {
        std::cout << "missing input and output ports" << std::endl;
        exit(84);
    }
    int inputPort = static_cast<int>(strtol(av[1], &av[1] + strlen(av[1]), 10));
    int outputPort =  static_cast<int>(strtol(av[2], &av[2] + strlen(av[2]), 10));

    connWindow.show();
    Babel::Management::LibHandler lib_handler;

    Babel::Networking::ClientUDP udp(nullptr, nullptr,  inputPort, outputPort);

//    udp.HelloUDP();

    return app.exec();
}