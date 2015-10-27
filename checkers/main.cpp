#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

#include "menudialog.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/Qt.png"));
    splash->show();

    MainWindow *mainWindow = new MainWindow;
    MenuDialog *menuDialog = new MenuDialog(mainWindow);

    QTimer::singleShot(1000, splash, SLOT(close()));
    QTimer::singleShot(1000, menuDialog, SLOT(show()));

    QObject::connect(menuDialog, SIGNAL(finished(int)), mainWindow, SLOT(show()));
    QObject::connect(menuDialog, SIGNAL(closeGame()), mainWindow, SLOT(close()));

    return app.exec();
}
