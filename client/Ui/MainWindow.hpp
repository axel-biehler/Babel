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
        class MainWindow : public QWidget {
            Q_OBJECT
        public:
            MainWindow(Babel::Networking::Client *cli);

        private:
            QHBoxLayout _mainLayout;
            QWidget _leftWidget;
            QVBoxLayout _leftLayout;
            QScrollArea _friendsScrollArea;
            QWidget _friendsContainer;
            QVBoxLayout _friendsInnerLayout;
            QPushButton _friendsButton;
            std::shared_ptr<ChatWidget> _chatWidget;
            Babel::Networking::Client *_cli;

        private slots:
            void showFriends();
            void onPacketReceived(Babel::Networking::RawPacket packet);
        };
    }
}