#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

#include "optionscreen.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/Qt.png"));
    splash->show();

    OptionScreen startScreen;
    MainWindow main;

    QTimer time;
    time.singleShot(1000, splash, SLOT(close()));
    time.singleShot(1000, &startScreen, SLOT(exec()));

    return app.exec();
}
