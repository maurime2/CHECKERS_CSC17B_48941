#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QList>
#include "tile.h"

class Board : public QWidget
{
    Q_OBJECT

public:
    Board(QWidget *parent = 0);
    QList<Tile *> tiles;

    // holds integer representing index of start/end tile
    int startLoc;
    int endLoc;
    bool startSelected;
    
    //functions
    bool setStartLoc(int loc);
    void unhighlight();
    void clearMoves();
    void highlight();
    bool tileIsEmpty(int loc);
    void determineMoves(int loc);
    void makeMove();
    void updatePiece(int loc);
    void updateBoard();
    void kingCheck(int loc);

    // returns tile location resulting from specified move
    int forwardLeft(int loc);
    int forwardRight(int loc);
    int forwardLeftJump(int loc);
    int forwardRightJump(int loc);
    int backwardLeft(int loc);
    int backwardRight(int loc);
    int backwardLeftJump(int loc);
    int backwardRightJump(int loc);

    bool checkMove(int start, int end);
    // checks for each possible move
    bool forwardLeftisValid(int start);
    bool forwardRightisValid(int start);
    bool forwardLeftJumpIsValid(int start);
    bool forwardRightJumpIsValid(int start);
    bool backwardLeftisValid(int start);
    bool backwardRightisValid(int start);
    bool backwardLeftJumpisValid(int start);
    bool backwardRightJumpisValid(int start);


    QList<int> moves;
signals:

public slots:
    void handleClick(int loc);

};

#endif // BOARD_H
