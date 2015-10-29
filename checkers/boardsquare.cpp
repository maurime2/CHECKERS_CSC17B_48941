

#include "boardsquare.h"

BoardSquare::BoardSquare(QWidget *parent, Qt::WindowFlags f)
    :QLabel(parent,f){
    active = false;
}

BoardSquare::BoardSquare(bool playable, QString &text, QWidget *parent, Qt::WindowFlags f)
    :QLabel(parent,f){
    // Set whether this square is part of the playable interface
    active = playable;

    this->setMargin(0);
    QPixmap image(text);

    // Now set the label's pixmap
    this->setPixmap(image);
}

void BoardSquare::activate(bool newState){
    if(active!=newState){
        active = newState;
        emit activated(newState);
    }
}

//BoardSquare::updateSquare(Piece &piece){
//}

