#include <QApplication>
#include <QWindow>
#include <QLabel>
#include "Ui/ConnectionWindow/ConnexionPage.hpp"
#include "Ui/ConnectionWindow/Window.hpp"

int main(int ac, char **av)
{
    QApplication app{ac, av};

    Babel::Ui::Window win;
    win.show();

    return app.exec();
}