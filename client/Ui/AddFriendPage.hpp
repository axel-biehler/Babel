#pragma once

#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

namespace Babel {
    namespace Ui {
        class AddFriendPage : public QWidget {
        public:
            AddFriendPage();

        private:
            QFormLayout _layout;
            QLineEdit _usernameLineEdit;
            QPushButton _addButton;

        };
    }
}