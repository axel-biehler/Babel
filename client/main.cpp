#include <QApplication>
#include <QWindow>
#include <QLabel>
#include <iostream>
#include "Audio/Portaudio.hpp"
#include "Audio/Opus.hpp"
#include "Networking/Client.hpp"
#include "Ui/ConnectionWindow/ConnectionWindow.hpp"

int main(int ac, char **av)
{
    //QCoreApplication app(ac, av);
    QApplication app(ac, av);
    //Babel::Networking::Client cli(av[1], std::stoi(av[2]));

    //cli.start();
    Babel::Ui::ConnectionWindow win;
    win.show();
    return app.exec();
}