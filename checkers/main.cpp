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

    MainWindow *mainWindow = new MainWindow;
    OptionScreen *mainMenu = new OptionScreen(mainWindow);
    mainMenu->setModal(true);

    QTimer::singleShot(1000, splash, SLOT(close()));
    QTimer::singleShot(1000, mainWindow, SLOT(showFullScreen()));
    QTimer::singleShot(1000, mainMenu, SLOT(show()));

    return app.exec();
}
