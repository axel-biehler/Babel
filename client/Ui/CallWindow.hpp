#pragma once

#include <memory>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <Ui/ChatWidget.hpp>
#include <Networking/Client.hpp>

namespace Babel {
    namespace Ui {
        enum CallStatus {
            WaitingForAnswer,
            Receiving,
            Call,
        };

        class CallWindow : public QWidget {
            Q_OBJECT
        public:
            CallWindow(Babel::Networking::Client *cli, CallStatus status, int otherId, const std::string &otherUsername);

        private:
            QVBoxLayout _mainLayout;
            QLabel _titleLabel;
            QPushButton _actionButton;
            Babel::Networking::Client *_cli;
            CallStatus _status;
            int _otherId;
            std::string _otherUsername;

        private slots:
            void actionButton();
            void onPacketReceived(Babel::Networking::RawPacket packet);
        };
    }
}