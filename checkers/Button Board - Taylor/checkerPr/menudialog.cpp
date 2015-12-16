#include <QPushButton>
#include <QVBoxLayout>

#include "menudialog.h"

MenuDialog::MenuDialog(QWidget *parent) : QDialog(parent)
{
    continueButton = new QPushButton("Continue");
    newButton = new QPushButton("New Game");
    loadButton = new QPushButton("Load Game");
    quitButton = new QPushButton("Quit");
    optionsButton = new QPushButton("Options");

    newButton->setStyleSheet("QPushButton {background-color:white}");
    continueButton->setStyleSheet("QPushButton {background-color:white}");
    loadButton->setStyleSheet("QPushButton {background-color:white}");
    quitButton->setStyleSheet("QPushButton {background-color:white}");
    optionsButton->setStyleSheet("QPushButton {background-color:white}");

    connect(this, SIGNAL(finished(int)), parent, SLOT(show()));
    connect(this, SIGNAL(closeGame()), parent, SLOT(close()));

    connect(newButton, SIGNAL(clicked(bool)), parent, SLOT(resetB()));
    connect(newButton, SIGNAL(clicked(bool)), this, SLOT(close()));

    connect(continueButton, SIGNAL(clicked(bool)), parent, SLOT(open()));
    connect(continueButton, SIGNAL(clicked(bool)), this, SLOT(close()));

    connect(loadButton, SIGNAL(clicked(bool)), parent, SLOT(open()));
    connect(loadButton, SIGNAL(clicked(bool)), this, SLOT(close()));

    connect(quitButton, SIGNAL(clicked(bool)), this, SLOT(quitClicked()));

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(newButton);
    layout->addWidget(continueButton);
    layout->addWidget(loadButton);
    layout->addWidget(optionsButton);
    layout->addWidget(quitButton);
    layout->setContentsMargins(250, 330, 250, 330);
    setLayout(layout);
    //this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    setWindowTitle("Checkers");

    QPalette backGround;

    backGround.setBrush(this->backgroundRole(),
                  QBrush(QImage(":/images/background.jpg")));
    this->setPalette(backGround);
}

void MenuDialog::quitClicked()
{
    if(this->quitButton)
    {
        emit closeGame();
    }
}
