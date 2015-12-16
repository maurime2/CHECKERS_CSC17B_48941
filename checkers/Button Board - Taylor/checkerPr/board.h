#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QList>
#include "tile.h"
#include <gameoverdialog.h>

class Board : public QWidget
{
    Q_OBJECT

public:
    Board(QWidget *parent = 0);
    QList<Tile *> tiles;
    GameOverDialog *over;
    // holds integer representing index of start/end tile
    int startLoc;
    int endLoc;
    bool startSelected;

    bool playersTurn;
    bool computersMove;
    bool jumpOcc;
    bool jumpTurn;
    bool playerWins;
    bool playerLoses;

    QString lastMovePlayer;
    QString lastMoveEnemy;

    // functions following move
    bool checkForWin();
    bool checkForLoss();
    bool checkForKing(int loc);
    bool checkForJump(int loc);

    //functions
    bool setStartLoc(int loc);
    void unhighlight();
    void clearMoves();
    void highlight();
    bool tileIsEmpty(int loc);
    bool determineMoves(int loc);
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

    void computerTurn();
    bool determineComputerMoves(int);

    // holds list of all available moves
    // Is filled upon a valid start location being set
    QList<int> moves;
    QList<int> computerMoves;
    QList<QString> moveNames;

    // end of game
    void gameOver(bool);

signals:
    void updateLastMoves(QString,QString);
    void endScreen(bool win);
    void returnToMenu();
    void toClose();
public slots:
    void handleClick(int loc);
    void em();                  //emitter
    void resetBoard();
    void leave();
    void backToMenu();

};

#endif // BOARD_H
