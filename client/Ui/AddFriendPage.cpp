#include "AddFriendPage.hpp"

Babel::Ui::AddFriendPage::AddFriendPage() {
    _usernameLineEdit.setPlaceholderText("Username");
    _usernameLineEdit.setFixedHeight(28);
    _usernameLineEdit.setFont(QFont("Roboto", 10));
    _addButton.setFont(QFont("Roboto", 10));
    _addButton.setText("Add");

    _layout.addRow("Username:", &_usernameLineEdit);
    _layout.addRow("", &_addButton);
    _layout.setSpacing(10);
    setLayout(&_layout);
}
