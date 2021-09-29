//
// Created by max on 27/09/2021.
//

#ifndef BABEL_CONNEXIONPAGE_HPP
#define BABEL_CONNEXIONPAGE_HPP

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>

class ConnexionPage : public QWidget {
public:
    ConnexionPage(QWidget *parent = 0);
    ~ConnexionPage() = default;
private:
    QLineEdit _input;
    QFormLayout _layout;
};

#endif //BABEL_CONNEXIONPAGE_HPP
