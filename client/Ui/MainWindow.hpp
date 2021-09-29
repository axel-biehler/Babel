#pragma once

#include <memory>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <Ui/ChatWidget.hpp>

namespace Babel {
    namespace Ui {
        class MainWindow : public QWidget {
            Q_OBJECT
        public:
            MainWindow();

        private:
            QHBoxLayout _mainLayout;
            QWidget _leftWidget;
            QVBoxLayout _leftLayout;
            QPushButton _friendsButton;
            std::shared_ptr<ChatWidget> _chatWidget;

        private slots:
            void showFriends();
        };
    }
}