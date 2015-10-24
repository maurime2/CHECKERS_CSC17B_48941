#include <QPushButton>
#include <QVBoxLayout>

#include "mainwindow.h"
#include "optionscreen.h"

OptionScreen::OptionScreen(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Checkers");

    continueButton = new QPushButton("Continue");
    newButton = new QPushButton("New Game");
    loadButton = new QPushButton("Load Game");
    quitButton = new QPushButton("Quit");

    connect(newButton, SIGNAL(clicked()), parent, SLOT(newFile()));
    connect(newButton, SIGNAL(clicked()), this, SLOT(close()));

    connect(continueButton, SIGNAL(clicked()), parent, SLOT(show()));
    connect(continueButton, SIGNAL(clicked()), this, SLOT(close()));

    connect(loadButton, SIGNAL(clicked()), parent, SLOT(open()));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(close()));

    connect(quitButton, SIGNAL(clicked()), parent, SLOT(close()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *layout = new QVBoxLayout;

    setLayout(layout);
    layout->addWidget(newButton);
    layout->addWidget(continueButton);
    layout->addWidget(loadButton);
    layout->addWidget(quitButton);
    layout->setContentsMargins(80, 50, 80, 50);
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
}


