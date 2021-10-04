#include "ChatWidget.hpp"
#include "MessageWidget.hpp"
#include <QScrollBar>

Babel::Ui::ChatWidget::ChatWidget(const std::string &username, int id) : _userId(id) {
    setLayout(&_mainLayout);

    _mainLayout.addLayout(&_topLayout);
    _userImageLabel.setPixmap(QPixmap("images/avatar.png").scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    _topLayout.addWidget(&_userImageLabel);
    _usernameLabel.setText(username.c_str());
    _usernameLabel.setFont(QFont("Roboto", 14));
    _topLayout.addSpacerItem(new QSpacerItem(4, 4));
    _topLayout.addWidget(&_usernameLabel);
    _topLayout.addStretch(1);
    _callButton.setIcon(QIcon("images/phone.png"));
    _callButton.setIconSize(QSize(20, 20));
    _callButton.setFixedSize(32, 32);
    _callButton.setFlat(true);
    _callButton.setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    _topLayout.addWidget(&_callButton);

    _mainLayout.addSpacerItem(new QSpacerItem(10, 8));
    _mainLayout.addWidget(&_outerChat, 1);
    _outerChat.setLayout(&_outerLayout);
    _outerLayout.addWidget(&_messagesScrollArea);
    _messagesScrollArea.setParent(&_outerChat);
    _messagesScrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    _messagesScrollArea.setWidgetResizable(true);
    _messagesScrollArea.setWidget(&_innerChat);
    _innerLayout.setAlignment(Qt::AlignTop);
    _innerChat.setLayout(&_innerLayout);
    for (int i = 0; i < 30; i++)
        _innerLayout.addWidget(new MessageWidget("Friend " + std::to_string(i + 1), "Hello mate!"));

    auto scrollbar = _messagesScrollArea.verticalScrollBar();
    QObject::connect(scrollbar, &QScrollBar::rangeChanged, this, &ChatWidget::moveScrollBarToBottom);

    _mainLayout.addLayout(&_bottomLayout);
    _chatLineEdit.setPlaceholderText("Your message...");
    _chatLineEdit.setFixedHeight(32);
    _chatLineEdit.setFont(QFont("Roboto", 10));
    _bottomLayout.addWidget(&_chatLineEdit, 1);
    _sendButton.setIcon(QIcon("images/sent.png"));
    _sendButton.setIconSize(QSize(20, 20));
    _sendButton.setFixedSize(32, 32);
    _sendButton.setFlat(true);
    _sendButton.setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    _bottomLayout.addWidget(&_sendButton);
}

void Babel::Ui::ChatWidget::moveScrollBarToBottom(int min, int max) {
    _messagesScrollArea.verticalScrollBar()->setValue(max);
}
