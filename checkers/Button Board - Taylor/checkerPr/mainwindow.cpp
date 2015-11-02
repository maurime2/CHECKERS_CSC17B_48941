#include <QGridLayout>
#include <QWidget>
#include "mainwindow.h"
#include "board.h"
#include "tile.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //QWidget *Widget = new QWidget(this);
    this->setFixedSize(400,400);

    // this central QWidget could be subclassed as a custom Board widget
    Board *board = new Board(this);
    this->setCentralWidget(board);

    // this list, which holds the tiles/buttons could be a member variable of the Board class

    QGridLayout *layout = new QGridLayout();
    board->setLayout(layout);
    layout->setSpacing(0);
    layout->setMargin(0);

    // Creates each of the TileButtons, adds them to the layout
    for (int i = 0; i < 32; i++)
    {
        layout->addWidget(board->tiles[i], i/4,(i - ((i/4)*4))*2 + (i/4)%2);
    }
}


