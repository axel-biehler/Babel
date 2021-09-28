#include "AddFriendPage.hpp"

Babel::Ui::AddFriendPage::AddFriendPage() {
    _usernameLineEdit.setPlaceholderText("Username");
    _usernameLineEdit.setFixedHeight(28);
    _addButton.setText("Add");

    _layout.addRow("Username", &_usernameLineEdit);
    _layout.addRow("", &_addButton);

    setLayout(&_layout);
}
