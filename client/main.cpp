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
    return app.exec();
}