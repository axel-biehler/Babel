#include "FriendsWindow.hpp"
#include "AddFriendPage.hpp"
#include "FriendInvitesPage.hpp"

Babel::Ui::FriendsWindow::FriendsWindow() {
    setFixedSize(600, 400);
    setWindowTitle("Friends");

    _mainTabWidget.setParent(this);
    _mainTabWidget.setFixedSize(width(), height());

    auto addFriendsPage = new AddFriendPage;
    auto friendInvitesPage = new FriendInvitesPage;

    _mainTabWidget.addTab(addFriendsPage, "Add a friend");
    _mainTabWidget.addTab(friendInvitesPage, "Pending invites");

    show();
}
