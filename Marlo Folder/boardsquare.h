#ifndef BOARDSQUARE
#define BOARDSQUARE

#include <QWidget>
#include <QLabel>
#include <QPixmap>


// User Libraries
#include "piece.h"

class BoardSquare:public QLabel{
    Q_OBJECT

public:
    // Default constructor
    explicit BoardSquare(QWidget *parent=0, Qt::WindowFlags f=0);
    // Main constructor
    explicit BoardSquare(bool playable, QString & text, QWidget *parent=0, Qt::WindowFlags f=0);

signals:
    //void pieceChange();
    void activated(bool newState);

public slots:
    //void updateSquare(Piece& piece);

    // Activates and deactivars square as playable
    void activate(bool newState);

private:

    // True if this square is part of the game
    bool active;

    // Piece currently occupying this square. If null,
    // there is no piece occupying the square.
    //Piece *occupierPiece;

};

#endif // BOARDSQUARE

