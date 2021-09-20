#include <QApplication>
#include <QWindow>
#include <QLabel>

int main(int ac, char **av)
{
    QApplication app{ac, av};

    QLabel label{};
    label.setText("How are you?");
    label.show();

    return app.exec();
}