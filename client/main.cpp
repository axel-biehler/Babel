#include <QApplication>
#include <Ui/ConnectionWindow/ConnectionWindow.hpp>
#include <Networking/Client.hpp>
#include <Networking/ClientUdp.hpp>
#include <iostream>
#include "Networking/Packets/PacketAudio.hpp"

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

/*
    if (ac < 3) {
        std::cout << "missing input and output ports" << std::endl;
        exit(84);
    }
    int inputPort = static_cast<int>(strtol(av[1], &av[1] + strlen(av[1]), 10));
    int outputPort =  static_cast<int>(strtol(av[2], &av[2] + strlen(av[2]), 10));

 std::vector<unsigned char> test;

    test.push_back('b');
    test.push_back('i');
    test.push_back('t');
    test.push_back('e');
    Babel::Networking::Packets::PacketAudio packet_audio(test);
    auto str = packet_audio.serialize().toStdString();
    Babel::Networking::RawPacket deserialize(std::vector<char>(str.begin(), str.end()));
    if (deserialize.getPacketType() == Babel::Networking::PacketAudio)
        std::cout << "incredible !" << std::endl;
    std::cout << "deserialized = ";
    Babel::Networking::Packets::PacketAudio deserialize2(packet_audio.serialize().getData());
    auto payload = deserialize2.getSample();
    for (unsigned char c : payload)
        std::cout << c;
    std::cout << std::endl;
    exit(88);
 */