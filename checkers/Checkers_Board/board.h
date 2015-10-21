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

//#include <QGraphicsItem>
//#include <QPainter>

class Board:public QWidget{
    Q_OBJECT

public:

    // Default constructor
    Board();

    // Main constructor
    //****************************************
    // Creates a board of n rows x n columns *
    //****************************************
    Board(const int& row, const int& column);



public slots:

signals:


private slots:

private:
    // Constants
    static const int DEFAULTSIZE=8;

    // Main board
    QLabel *board;



};

#endif // BOARD

