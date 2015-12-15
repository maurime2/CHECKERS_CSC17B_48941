#include "tile.h"
#include "board.h"

Tile::Tile(QWidget *parent) :  QPushButton(parent)
{
    // connect tile to board; a click signal is sent to the board object where it is
    // handled and checked 
    this->setMinimumSize(50,50);
    this->setFlat(true);
    this->setAutoFillBackground(true);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Button, Qt::darkRed);
    this->setPalette(pal);

    //set tile activity enum

    QObject::connect(this, SIGNAL(clicked(bool)), this, SLOT(emmiter()));
    QObject::connect(this, SIGNAL(clicked(bool)), parent, SLOT(em()));
    QObject::connect(this, SIGNAL(setLocation(int)), parent, SLOT(handleClick(int)));

}
//signal

void Tile::emmiter()
{
    int loc = this->location;
    emit setLocation(loc);
}

