//
// Created by max on 27/09/2021.
//

#ifndef BABEL_CONNECTIONPAGE_HPP
#define BABEL_CONNECTIONPAGE_HPP

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <Networking/Client.hpp>
//#include "ConnectionWindow.hpp"

namespace Babel::Ui {
    class ConnectionWindow;
}

namespace Babel {
    namespace Ui {
        class ConnectionPage : public QWidget {
        public:
            ConnectionPage(Babel::Networking::Client *cli, Babel::Ui::ConnectionWindow *win);
            ~ConnectionPage() override;

            void handlePacketRespLogin(Babel::Networking::RawPacket rawPacket);
            void handlePacketRespRegister(Babel::Networking::RawPacket rawPacket);
        private:
            QLineEdit _input;
            QLineEdit _pass;
            QLineEdit _ip;
            QVBoxLayout _mainLayout;
            QHBoxLayout _btnLayout;
            QWidget _btnWidget;
            QLabel _text;
            QPushButton _register;
            QPushButton _login;
            Babel::Networking::Client *_cli;
            Babel::Ui::ConnectionWindow *_win;

        private slots:
            void Register();
            void Login();
            void OnPacketReceived(Babel::Networking::RawPacket packet);
        };
    }
}

#endif //BABEL_CONNECTIONPAGE_HPP
