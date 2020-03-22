#include <QApplication>
#include "MainStackedWidget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPushButton* quit_button = new QPushButton("Exit");
    QObject::connect(quit_button, &QPushButton::pressed, &a, &QApplication::quit);

    MainStackedWidget sw(quit_button);
    sw.show();

    return a.exec();
}
