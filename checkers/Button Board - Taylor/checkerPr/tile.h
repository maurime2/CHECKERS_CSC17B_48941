#ifndef TILE_H
#define TILE_H


#include <QPushButton>

class Tile : public QPushButton
{
    Q_OBJECT

public:
    Tile(QWidget *parent = 0);
    int location;

    // holds state of tile.
    enum State {EMPTY = 0, REDPIECE = 1, REDKING = 2, BLACKPIECE =3, BLACKKING= 4};
    State state;

    // value represents tile in relation to most recent move
    enum Activity {MOVEDFROM, MOVEDTO, JUMPED, NOACTIVITY};
    Activity activity;

signals:
    void setLocation(int );
public slots:
    void emmiter();

};

#endif // TILE_H
