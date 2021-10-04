#include "MessageWidget.hpp"

Babel::Ui::MessageWidget::MessageWidget(const std::string &username, const std::string &content) {
    setLayout(&_mainLayout);
    _mainLayout.setAlignment(Qt::AlignTop);
    _mainLayout.addWidget(&_usernameLabel);
    _mainLayout.addWidget(&_contentLabel);

    _usernameLabel.setText(username.c_str());
    _usernameLabel.setFont(QFont("Roboto", 10));
    _usernameLabel.setStyleSheet("font-weight: bold;");

    _contentLabel.setText(content.c_str());
    _contentLabel.setFont(QFont("Roboto", 10));
}
