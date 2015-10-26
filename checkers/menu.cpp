#include <QPushButton>
#include <QVBoxLayout>

#include "menu.h"

Menu::Menu(QWidget *parent) : QDialog(parent)
{
    continueButton = new QPushButton("Continue");
    newButton = new QPushButton("New Game");
    loadButton = new QPushButton("Load Game");
    quitButton = new QPushButton("Quit");
    optionsButton = new QPushButton("Options");

    connect(newButton, SIGNAL(clicked()), parent, SLOT(newFile()));
    connect(newButton, SIGNAL(clicked()), this, SLOT(close()));

    connect(continueButton, SIGNAL(clicked()), parent, SLOT(open()));
    connect(continueButton, SIGNAL(clicked()), this, SLOT(close()));

    connect(loadButton, SIGNAL(clicked()), parent, SLOT(open()));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(close()));

    connect(quitButton, SIGNAL(clicked()), parent, SLOT(close()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(newButton);
    layout->addWidget(continueButton);
    layout->addWidget(loadButton);
    layout->addWidget(optionsButton);
    layout->addWidget(quitButton);
    layout->setContentsMargins(250, 330, 250, 330);
    setLayout(layout);
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    setWindowTitle("Checkers");

    QPalette backGround;

    backGround.setBrush(this->backgroundRole(),
                  QBrush(QImage(":/images/background.jpg")));
    this->setPalette(backGround);
}
