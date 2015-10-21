#include <QPushButton>
#include <QVBoxLayout>

#include "mainwindow.h"
#include "optionscreen.h"

OptionScreen::OptionScreen(QWidget *parent) : QDialog(parent)
{
    MainWindow *mainWindow = new MainWindow;
    continueButton = new QPushButton("Continue");
    newButton = new QPushButton("New Game");
    loadButton = new QPushButton("Load Game");
    quitButton = new QPushButton("Quit");

    connect(continueButton, SIGNAL(clicked()), mainWindow, SLOT(show()));
    connect(continueButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *layout = new QVBoxLayout;

    setLayout(layout);
    layout->addWidget(continueButton);
    layout->addWidget(newButton);
    layout->addWidget(loadButton);
    layout->addWidget(quitButton);
    layout->setContentsMargins(80, 50, 80, 50);
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    setWindowTitle("Checkers");
}


