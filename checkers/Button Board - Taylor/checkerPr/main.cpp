#include "mainwindow.h"
#include "menudialog.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/Qt.png"));
    splash->show();
*/

    MainWindow *w = new MainWindow;
    //menuDialog = new MenuDialog(w);
    //QTimer::singleShot(1000, splash, SLOT(close()));
    //QTimer::singleShot(1000, menuDialog, SLOT(show()));
    //w.show();

    return a.exec();
}
