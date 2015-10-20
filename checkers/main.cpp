#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

#include "startscreen.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/Qt.png"));
    splash->show();

    StartScreen startScreen;

    QTimer::singleShot(1000, splash, SLOT(close()));
    QTimer::singleShot(1000, &startScreen, SLOT(show()));

    return app.exec();
}
