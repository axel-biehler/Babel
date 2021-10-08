#include "CallWindow.hpp"

Babel::Ui::CallWindow::CallWindow() {
    setWindowTitle("Call");
    setFixedSize(300, 200);
    setLayout(&_mainLayout);

    _mainLayout.addWidget(&_titleLabel);
    _mainLayout.addWidget(&_hangupButton);

    _titleLabel.setText("Call with Joe");
    _titleLabel.setFont(QFont("Roboto", 12));
    _titleLabel.setAlignment(Qt::AlignCenter);

    _hangupButton.setIcon(QIcon("images/hangup.png"));
    _hangupButton.setIconSize(QSize(32, 32));
    _hangupButton.setText("Hang up");
    _hangupButton.setFont(QFont("Roboto", 10));
}
