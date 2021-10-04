#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

namespace Babel {
    namespace Ui {
        class MessageWidget : public QWidget {
        public:
            MessageWidget(const std::string &username, const std::string &content);

        private:
            QVBoxLayout _mainLayout;
            QLabel _usernameLabel;
            QLabel _contentLabel;
        };
    }
}

