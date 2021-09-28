#include <QVBoxLayout>
#include <QLabel>
#include "FriendInvitesPage.hpp"

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
        QLabel *label = new QLabel("Hello " + QString::number(i));
        label->setFixedHeight(16);
        _innerLayout.addWidget(label);
    }

}
