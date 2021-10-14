//
// Created by max on 27/09/2021.
//

#include <Networking/Packets/PacketCmdRegister.hpp>
#include <Networking/Packets/PacketCmdLogin.hpp>
#include <QMessageBox>
#include <iostream>
#include <Networking/Packets/PacketRespRegister.hpp>
#include <Ui/MainWindow.hpp>
#include <Networking/Packets/PacketRespLogin.hpp>
#include "ConnectionPage.hpp"
#include "ConnectionWindow.hpp"

Babel::Ui::ConnectionPage::ConnectionPage(Babel::Networking::Client *cli, Babel::Ui::ConnectionWindow *win) : _cli(cli), _win(win) {
    _text.setText("Enter connection informations :");
    _text.setAlignment(Qt::AlignCenter);
    _mainLayout.addWidget(&_text);
    _input.setPlaceholderText("Username");
    _pass.setPlaceholderText("Password");
    _ip.setPlaceholderText("IP");
    _mainLayout.addWidget(&_input, Qt::AlignCenter);
    _mainLayout.addWidget(&_pass, Qt::AlignCenter);
    _mainLayout.addWidget(&_ip, Qt::AlignCenter);
    _register = new QPushButton("Sign Up", this);
    _login = new QPushButton("Sign In", this);
    _mainLayout.addWidget(&_btnWidget);
    _btnWidget.setLayout(&_btnLayout);
    _btnLayout.addWidget(_login);
    _btnLayout.addWidget(_register);
    this->setLayout(&_mainLayout);

    QObject::connect(_register, &QPushButton::released, this, &Babel::Ui::ConnectionPage::Register);
    QObject::connect(_login, &QPushButton::released, this, &Babel::Ui::ConnectionPage::Login);
    QObject::connect(_cli, &Babel::Networking::Client::packetReceive, this, &Babel::Ui::ConnectionPage::OnPacketReceived);
}

void Babel::Ui::ConnectionPage::Register()
{
    auto split = _ip.text().split(':');
    if (split.length() < 2)
        return;
    if (!_cli->isConnected())
        _cli->start(split[0], split[1].toInt());
    Babel::Networking::Packets::PacketCmdRegister packetCmdRegister{_input.text().toStdString(), _pass.text().toStdString()};
    _cli->write(packetCmdRegister.serialize());
}

void Babel::Ui::ConnectionPage::Login()
{
    auto split = _ip.text().split(':');
    if (split.length() < 2)
        return;
    if (!_cli->isConnected())
        _cli->start(split[0], split[1].toInt());
    Babel::Networking::Packets::PacketCmdLogin packetCmdLogin{_input.text().toStdString(), _pass.text().toStdString()};
    _cli->write(packetCmdLogin.serialize());
}

void Babel::Ui::ConnectionPage::handlePacketRespLogin(Babel::Networking::RawPacket rawPacket)
{
    auto respLoginPacket = std::static_pointer_cast<Babel::Networking::Packets::PacketRespLogin>(rawPacket.deserialize());

    if (!respLoginPacket->getOk()) {
        QMessageBox::critical(this, "Could not login.", respLoginPacket->getErrorMessage().c_str());
        return;
    }
    _cli->setUserId(respLoginPacket->getUserId());
    Babel::Ui::MainWindow *mainWindow = new Babel::Ui::MainWindow(_cli);
    mainWindow->show();
    _win->hide();
}

void Babel::Ui::ConnectionPage::handlePacketRespRegister(Babel::Networking::RawPacket rawPacket)
{
    auto respRegisterPacket = std::static_pointer_cast<Babel::Networking::Packets::PacketRespRegister>(rawPacket.deserialize());

    if (!respRegisterPacket->getOk()) {
        QMessageBox::critical(this, "Could not register", respRegisterPacket->getErrorMessage().c_str());
        return;
    }
    auto split = _ip.text().split(':');
    if (split.length() < 2)
        return;
    if (!_cli->isConnected())
        _cli->start(split[0], split[1].toInt());
    Babel::Networking::Packets::PacketCmdLogin packetCmdLogin{_input.text().toStdString(), _pass.text().toStdString()};
    _cli->write(packetCmdLogin.serialize());
}

void Babel::Ui::ConnectionPage::OnPacketReceived(Babel::Networking::RawPacket packet) {

    switch (packet.getPacketType()) {
        case Networking::PacketRespLogin:
            handlePacketRespLogin(packet);
            break;
        case Networking::PacketRespRegister:
            handlePacketRespRegister(packet);
            break;
    }
}
