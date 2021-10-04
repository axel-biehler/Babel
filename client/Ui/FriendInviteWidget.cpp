#include "FriendInviteWidget.hpp"

Babel::Ui::FriendInviteWidget::FriendInviteWidget(const std::string &username, Babel::Ui::FriendInviteWidgetType type) {
    setLayout(&_mainLayout);
    _mainLayout.addWidget(&_userImageLabel);
    _mainLayout.addSpacerItem(new QSpacerItem(8, 8));
    _mainLayout.addWidget(&_usernameLabel);
    _mainLayout.addStretch();

    if (type == Sent) {
        _mainLayout.addWidget(&_sentLabel);
        _mainLayout.addSpacerItem(new QSpacerItem(6, 6));
    } else {
        _mainLayout.addWidget(&_acceptButton);
        _mainLayout.addWidget(&_denyButton);
    }

    _userImageLabel.setPixmap(QPixmap("images/avatar.png").scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    _usernameLabel.setText(username.c_str());
    _usernameLabel.setFont(QFont("Roboto", 10));

    _sentLabel.setPixmap(QPixmap("images/sent.png").scaled(22, 22, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    _acceptButton.setIcon(QIcon("images/accept.png"));
    _acceptButton.setIconSize(QSize(32, 32));
    _acceptButton.setFixedSize(32, 32);
    _acceptButton.setFlat(true);
    _acceptButton.setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    _denyButton.setIcon(QIcon("images/deny.png"));
    _denyButton.setIconSize(QSize(32, 32));
    _denyButton.setFixedSize(32, 32);
    _denyButton.setFlat(true);
    _denyButton.setStyleSheet("background-color: rgba(255, 255, 255, 0);");
}
