#include <QApplication>
#include <Ui/ConnectionWindow/ConnectionWindow.hpp>
#include <Networking/Client.hpp>
#include <Networking/ClientUdp.hpp>

int main(int ac, char **av)
{
    QApplication app(ac, av);
    Babel::Networking::Client cli;
    Babel::Ui::ConnectionWindow connWindow(&cli);

    connWindow.show();

    Babel::Networking::ClientUDP client_udp(nullptr, 4000, 4001);

    client_udp.startConnection("127.0.0.1", 4000, 4001);
    return app.exec();
}