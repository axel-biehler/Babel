#include "Networking/Client.hpp"

int main(int ac, char **av)
{
    QCoreApplication app(ac, av);
    Babel::Networking::Client cli(av[1], std::stoi(av[2]));

    cli.start();

    return app.exec();
}