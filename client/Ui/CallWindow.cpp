#include <Networking/Packets/PacketAcceptCall.hpp>
#include <Networking/Packets/PacketStartVoip.hpp>
#include <iostream>
#include "CallWindow.hpp"

Babel::Ui::CallWindow::CallWindow(Babel::Networking::Client *cli, Babel::Ui::CallStatus status, int otherId, const std::string &otherUsername) :
    _cli(cli), _status(status), _otherId(otherId), _otherUsername(otherUsername) {
    setWindowTitle("Call");
    setFixedSize(300, 200);
    setLayout(&_mainLayout);
    _cliUdp = new Networking::ClientUDP(nullptr, 0, 0);

    _mainLayout.addWidget(&_titleLabel);
    _mainLayout.addWidget(&_actionButton);

    _titleLabel.setText("Call with Joe");
    switch (status) {
        case WaitingForAnswer:
            _titleLabel.setText(QString("Calling ") + QString(otherUsername.c_str()) + QString("..."));
            _actionButton.setIcon(QIcon("images/hangup.png"));
            _actionButton.setText("Hang up");
            break;
        case Receiving:
            _titleLabel.setText(QString(otherUsername.c_str()) + QString(" is calling..."));
            _actionButton.setIcon(QIcon("images/phone.png"));
            _actionButton.setText("Accept");
            break;
        default: break;
    }
    _titleLabel.setFont(QFont("Roboto", 12));
    _titleLabel.setAlignment(Qt::AlignCenter);

    _actionButton.setIconSize(QSize(32, 32));
    _actionButton.setFont(QFont("Roboto", 10));

    QObject::connect(_cli, &Babel::Networking::Client::packetReceive, this, &CallWindow::onPacketReceived);
    QObject::connect(&_actionButton, &QPushButton::pressed, this, &CallWindow::actionButton);
}

void Babel::Ui::CallWindow::onPacketReceived(Babel::Networking::RawPacket packet) {
    if (packet.getPacketType() == Networking::PacketStartVoip) {
        _titleLabel.setText(QString("Call with ") + QString(_otherUsername.c_str()));
        _actionButton.setIcon(QIcon("images/hangup.png"));
        _actionButton.setText("Hang up");
        _status = CallStatus::Call;

        auto voip = std::static_pointer_cast<Networking::Packets::PacketStartVoip>(packet.deserialize());
        // start call
        _cliUdp->startConnection(voip->getIp(), voip->getListenPort(), voip->getSendPort());
        std::cout << voip->getIp() << " (" << voip->getListenPort() << "/" << voip->getSendPort() << ")" << std::endl;
    }
}

void Babel::Ui::CallWindow::actionButton() {
    if (_status == CallStatus::WaitingForAnswer) {
        delete this;
    } else if (_status == CallStatus::Receiving) {
        Networking::Packets::PacketAcceptCall packet{_otherId};
        _cli->write(packet.serialize());
    } else {
        // stop call
        _cliUdp->stopConnection();
        delete this;
    }
}
