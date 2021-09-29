#include <QVBoxLayout>
#include "FriendInvitesPage.hpp"
#include "FriendInviteWidget.hpp"

Babel::Ui::FriendInvitesPage::FriendInvitesPage() {
    setLayout(&_mainLayout);
    _scrollArea.setParent(this);
    _mainLayout.addWidget(&_scrollArea);
    _scrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    _scrollArea.setWidgetResizable(true);
    _scrollArea.setWidget(&_mainWidget);
    _innerLayout.setAlignment(Qt::AlignTop);
    _mainWidget.setLayout(&_innerLayout);

    for (int i = 0; i < 50; i++) {
        FriendInviteWidget *w = new FriendInviteWidget("John Doe", i % 2 == 0 ? Sent : Received);
        _innerLayout.addWidget(w);
    }

}
