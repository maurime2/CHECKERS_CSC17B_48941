#include "gameoverdialog.h"
#include <QGridLayout>

GameOverDialog::GameOverDialog(QWidget *parent) : QDialog(parent)
{
    playAgain = new QPushButton;
    playAgain->setText("Play Again");
    mainMenu = new QPushButton("Main Menu");
    quit = new QPushButton("Quit");

    playAgain->setStyleSheet("QPushButton {background-color:white}");
    mainMenu->setStyleSheet("QPushButton {background-color:white}");
    quit->setStyleSheet("QPushButton {background-color:white}");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(playAgain,1,0);
    layout ->addWidget(mainMenu,1, 1);
    layout ->addWidget(quit,1,2);

    setLayout(layout);
    //layout->insertSpacing(1,100);
    //layout->setGeometry(QRect(20,20,1,1));

    layout->setContentsMargins(250, 330, 250, 330);
    this->setStyleSheet("QDialog {background-image: url(:/images/icons/win.png)}");

    QObject::connect(playAgain, SIGNAL(clicked(bool)), parent, SLOT(resetBoard()));
    QObject::connect(playAgain, SIGNAL(clicked(bool)), this, SLOT(hide()));

    QObject::connect(mainMenu, SIGNAL(clicked(bool)), parent, SLOT(backToMenu()));
    //QObject::connect(mainMenu, SIGNAL(clicked(bool)), parent, SLOT(close()));
    QObject::connect(mainMenu, SIGNAL(clicked(bool)), this, SLOT(close()));


    QObject::connect(quit, SIGNAL(clicked(bool)), parent, SLOT(leave()));
    QObject::connect(quit, SIGNAL(clicked(bool)), this, SLOT(close()));

}

void GameOverDialog::winOrLoss(bool win)
{
    if (!win)
    {
        playAgain->setStyleSheet("QPushButton {background-color:blue;color: white}");
        mainMenu->setStyleSheet("QPushButton {background-color:blue;color:white}");
        quit->setStyleSheet("QPushButton {background-color:blue;color:white}");

        this->setStyleSheet("QWidget {background-image: url(:/images/icons/loss.png)}");

    }
}
