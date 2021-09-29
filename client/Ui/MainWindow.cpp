#include <QLabel>
#include "MainWindow.hpp"
#include "FriendsWindow.hpp"

Babel::Ui::MainWindow::MainWindow() {
    setWindowTitle("Babel");
    setMinimumSize(800, 600);
    setLayout(&_mainLayout);

    _chatWidget = std::make_shared<Babel::Ui::ChatWidget>("John", 4);

    _mainLayout.addWidget(&_leftWidget);
    _leftWidget.setFixedWidth(250);
    _leftWidget.setLayout(&_leftLayout);
    _leftLayout.addWidget(new QPushButton("Friend 1"));
    _leftLayout.addWidget(new QPushButton("Friend 2"));
    _leftLayout.addWidget(new QPushButton("Friend 3"));
    _leftLayout.addStretch();
    _leftLayout.addWidget(&_friendsButton);

    _friendsButton.setText("Manage friends");
    _friendsButton.setFont(QFont("Roboto", 11));
    _friendsButton.setFixedHeight(32);

    _mainLayout.addWidget(_chatWidget.get(), 1);

    connect(&_friendsButton, &QPushButton::released, this, &MainWindow::showFriends);
}

void Babel::Ui::MainWindow::showFriends() {
    (new FriendsWindow())->show();
}
