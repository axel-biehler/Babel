#include "FriendsWindow.hpp"
#include "AddFriendPage.hpp"
#include "FriendInvitesPage.hpp"

Babel::Ui::FriendsWindow::FriendsWindow(Babel::Networking::Client *cli) : _cli(cli) {
    setFixedSize(600, 400);
    setWindowTitle("Friends");

    _mainTabWidget.setParent(this);
    _mainTabWidget.setFixedSize(width(), height());
    _mainTabWidget.setFont(QFont("Roboto", 10));

    auto addFriendsPage = new AddFriendPage(_cli);
    auto friendInvitesPage = new FriendInvitesPage;

    _mainTabWidget.addTab(addFriendsPage, "Add a friend");
    _mainTabWidget.addTab(friendInvitesPage, "Pending invites");

    show();
}
