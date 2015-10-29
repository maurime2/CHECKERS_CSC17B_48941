/*
 * Author: Marlo Zeroth
 * Course: CSC17B
 * October 16, 2015
 * Group Project: Checkers
 * This is the board.h file
 * This is the interface for Board class
 * It is used to draw the board and to
 * generate valid playing positions for the
 * game.
 */



#ifndef BOARD
#define BOARD

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QMap>
#include <QString>
#include <QGridLayout>


// User libraries
#include "piece.h"
#include "boardsquare.h"

//#include <QGraphicsItem>
//#include <QPainter>

class Board:public QWidget{
    Q_OBJECT

public:

    // Default constructor
    Board(QWidget *parent=0, Qt::WindowFlags f=0);

    // Destructor
    virtual ~Board();

    // Main constructor
    //****************************************
    // Creates a board of n rows x n columns *
    //****************************************
    //Board(const int& row, const int& column);



//public slots:
    // Updates the board with a piece's new position
    //updateBoard(int & /*square*/ /*newPosition*/);

//signals:

    // Emits signal if a board square is changed
    // such as a piece moves into the square or
    // out of that square
    //void boardChange(int /*board square*/);

//private slots:

private:
    // Constants
    static const int DEFAULTSIZE=8;

    // Default square images
    QString *lightSquare;
    QString *darkSquare;

    // Main board
    QMap<int, BoardSquare*> playableSquares;
    QMap<int, BoardSquare*> nonPlayableSquares;




};

#endif // BOARD

