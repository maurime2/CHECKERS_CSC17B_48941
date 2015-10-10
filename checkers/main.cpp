#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/Qt.png"));
    splash->show();

    MainWindow window;

    QTimer::singleShot(3000, splash, SLOT(close()));
    QTimer::singleShot(3000, &window, SLOT(showFullScreen()));

    return app.exec();
}
