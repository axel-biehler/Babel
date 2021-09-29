#include <QApplication>
#include <QWindow>
#include <QLabel>
#include "Ui/ConnexionPage/ConnexionPage.hpp"
#include <QVBoxLayout>
#include <QStackedWidget>
#include "Ui/MenuPage/MenuPage.hpp"
#include "Ui/Window/Window.hpp"

int main(int ac, char **av)
{
    QApplication app{ac, av};

    Window *window = new Window();
    QStackedWidget *pages = new QStackedWidget();
    QVBoxLayout *layout = new QVBoxLayout();

    ConnexionPage *page = new ConnexionPage();

    pages->addWidget(page);
    layout->addWidget(pages);

    window->setLayout(layout);
    window->show();

    return app.exec();
}