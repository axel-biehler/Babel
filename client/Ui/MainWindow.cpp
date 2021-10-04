#include <QLabel>
#include "MainWindow.hpp"
#include "FriendsWindow.hpp"
#include "FriendItemWidget.hpp"

Babel::Ui::MainWindow::MainWindow() {
    setWindowTitle("Babel");
    setMinimumSize(800, 600);
    setLayout(&_mainLayout);

    _chatWidget = std::make_shared<Babel::Ui::ChatWidget>("John", 4);

    _mainLayout.addWidget(&_leftWidget);
    _leftWidget.setFixedWidth(250);
    _leftWidget.setLayout(&_leftLayout);
    _leftLayout.addWidget(&_friendsScrollArea, 1);
    _friendsScrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    _friendsScrollArea.setWidgetResizable(true);
    _friendsScrollArea.setParent(&_leftWidget);
    _friendsScrollArea.setWidget(&_friendsContainer);
    _friendsContainer.setLayout(&_friendsInnerLayout);
    _friendsInnerLayout.setAlignment(Qt::AlignTop);
    for (int i = 0; i < 3; i++)
        _friendsInnerLayout.addWidget(new FriendItemWidget("Friend " + std::to_string(i + 1)));
    _leftLayout.addWidget(&_friendsButton);

    _friendsButton.setText("Manage friends");
    _friendsButton.setFont(QFont("Roboto", 10));
    _friendsButton.setFixedHeight(32);

    _mainLayout.addWidget(_chatWidget.get(), 1);

    connect(&_friendsButton, &QPushButton::released, this, &MainWindow::showFriends);
}

void Babel::Ui::MainWindow::showFriends() {
    (new FriendsWindow())->show();
}
