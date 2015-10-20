#include <QPushButton>
#include <QVBoxLayout>

#include "mainwindow.h"
#include "startscreen.h"

StartScreen::StartScreen(QWidget *parent) : QDialog(parent)
{
    continueButton = new QPushButton("Continue");
    newButton = new QPushButton("New Game");
    loadButton = new QPushButton("Load Game");
    quitButton = new QPushButton("Quit");

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
