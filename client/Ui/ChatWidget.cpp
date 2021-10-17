#include "ChatWidget.hpp"
#include "MessageWidget.hpp"
#include <QScrollBar>
#include <Networking/Packets/PacketCmdListMessages.hpp>

Babel::Ui::ChatWidget::ChatWidget(const std::string &username, int id, Babel::Networking::Client *cli) : _userId(id), _cli(cli) {
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

    connect(&_sendButton, &QPushButton::released, this, &ChatWidget::sendMessage);
    Babel::Networking::Packets::PacketCmdListMessages messages;
    _cli->write(messages.serialize());
}

Babel::Ui::ChatWidget::ChatWidget(const Babel::Ui::ChatWidget &widget) : _userId(widget.getUID()), _username(widget.getUsername()), _cli(widget._cli)
{
    setLayout(&_mainLayout);

    _mainLayout.addLayout(&_topLayout);
    _userImageLabel.setPixmap(QPixmap("images/avatar.png").scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    _topLayout.addWidget(&_userImageLabel);
    _usernameLabel.setText(widget.getUsername().c_str());
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

    connect(&_sendButton, &QPushButton::released, this, &ChatWidget::sendMessage);
    Babel::Networking::Packets::PacketCmdListMessages messages;
    _cli->write(messages.serialize());
}

void Babel::Ui::ChatWidget::moveScrollBarToBottom(int min, int max) {
    _messagesScrollArea.verticalScrollBar()->setValue(max);
}

void Babel::Ui::ChatWidget::sendMessage() {

}

void Babel::Ui::ChatWidget::setUsername(std::string username) {
    _usernameLabel.setText(username.c_str());
}

void Babel::Ui::ChatWidget::setId(int id) {
    _userId = id;
}

std::string Babel::Ui::ChatWidget::getUsername() const {
    return _username;
}

int Babel::Ui::ChatWidget::getUID() const {
    return _userId;
}

void Babel::Ui::ChatWidget::setMessages(std::vector<Babel::Networking::Message> messages) {
    _messages = messages;
}

void Babel::Ui::ChatWidget::updateMessage(int uid) {
    std::vector<Babel::Networking::Message> messages;

    for (auto &mess : _messages) {
        if (mess.to == uid || mess.from == uid)
            messages.push_back(mess);
    }
    std::sort(messages.begin(), messages.end(), [](const Babel::Networking::Message &lhs, const Babel::Networking::Message &rhs) {
        return lhs.timestamp > rhs.timestamp;
    });
    for(auto &mess : messages) {
        _innerLayout.addWidget(new MessageWidget(mess.fromUsername, mess.body));
    }
}
