#pragma once

#include <memory>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <Ui/ChatWidget.hpp>

namespace Babel {
    namespace Ui {
        class CallWindow : public QWidget {
            Q_OBJECT
        public:
            CallWindow();
        private:
            QVBoxLayout _mainLayout;
            QLabel _titleLabel;
            QPushButton _hangupButton;
        };
    }
}