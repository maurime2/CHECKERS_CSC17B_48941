#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

#include "menu.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/Qt.png"));
    splash->show();

    MainWindow *mainWindow = new MainWindow;
    Menu *menu = new Menu(mainWindow);

    QTimer::singleShot(1000, splash, SLOT(close()));
    QTimer::singleShot(1000, menu, SLOT(show()));

    QObject::connect(menu, SIGNAL(finished(int)), mainWindow, SLOT(show()));

    return app.exec();
}
