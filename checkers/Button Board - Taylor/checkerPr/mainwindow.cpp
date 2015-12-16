#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include "mainwindow.h"
#include "board.h"
#include "tile.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //QWidget *Widget = new QWidget(this);
    this->setFixedSize(450,500);
    menu = new MenuDialog(this);
    menu->show();
    // this central QWidget could be subclassed as a custom Board widget
    Board *board = new Board(this);
    this->setCentralWidget(board);

    // this list, which holds the tiles/buttons could be a member variable of the Board class

    QGridLayout *layout = new QGridLayout;
    layout->setSpacing(0);
    layout->setMargin(0);

    QLabel *a = new QLabel;
    QLabel *bb = new QLabel;
    QLabel *c = new QLabel;
    QLabel *d = new QLabel;
    QLabel *e = new QLabel;
    QLabel *f = new QLabel;
    QLabel *g = new QLabel;
    QLabel *h = new QLabel;
    a->setText("A");
    bb->setText("B");
    c->setText("C");
    d->setText("D");
    e->setText("E");
    f->setText("F");
    g->setText("G");
    h->setText("H");

    a->setStyleSheet("QLabel {background-color:white;}");
    bb->setStyleSheet("QLabel {background-color:white;}");
    c->setStyleSheet("QLabel {background-color:white;}");
    d->setStyleSheet("QLabel {background-color:white;}");
    e->setStyleSheet("QLabel {background-color:white;}");
    f->setStyleSheet("QLabel {background-color:white;}");
    g->setStyleSheet("QLabel {background-color:white;}");
    h->setStyleSheet("QLabel {background-color:white;}");

    QLabel *one = new QLabel;
    QLabel *two = new QLabel;
    QLabel *three = new QLabel;
    QLabel *four = new QLabel;
    QLabel *five = new QLabel;
    QLabel *six = new QLabel;
    QLabel *seven = new QLabel;
    QLabel *eight = new QLabel;
    one->setText("1");
    two->setText("2");
    three->setText("3");
    four->setText("4");
    five->setText("5");
    six->setText("6");
    seven->setText("7");
    eight->setText("8");

    one->setStyleSheet("QLabel {background-color: white;}");
    two->setStyleSheet("QLabel {background-color: white;}");
    three->setStyleSheet("QLabel {background-color: white;}");
    four->setStyleSheet("QLabel {background-color: white;}");
    five->setStyleSheet("QLabel {background-color: white;}");
    six->setStyleSheet("QLabel {background-color: white;}");
    seven->setStyleSheet("QLabel {background-color: white;}");
    eight->setStyleSheet("QLabel {background-color: white;}");

    redLabel = new QLabel;
    blackLabel = new QLabel;
    redLabel->setText("Red:");
    blackLabel->setText("Black:");
    redLabel->setStyleSheet("QLabel {background-color:Gold;color:red; border:2px ridge black;font-family: Charcoal;font-style: normal;font-size: 12pt;font-weight: bold}");
    blackLabel->setStyleSheet("QLabel {background-color:Gold;color:black;border: 2px ridge black;font-family: Charcoal;font-style: normal;font-size: 12pt;font-weight: bold}");
    reset = new QPushButton();
    reset->setText("New Game");
    reset->setMaximumWidth(100);
    reset->setStyleSheet("QPushButton {background-color:white;color:black;border: 2px ridge black;font-family: Charcoal;font-style: normal;font-size: 12pt;font-weight: bold} QPushButton:hover {background-color:darkRed;color:black;} QPushButton:pressed {background-color:lightCoral;color:black}");

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(redLabel);
    bottomLayout->addWidget(reset);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(blackLabel);
    mainLayout->addLayout(layout);
    //mainLayout->addWidget(redLabel);
    mainLayout->addLayout(bottomLayout);
    board->setLayout(mainLayout);
    board->setStyleSheet("QWidget {border-color: 2px solid black;}");
    // Creates each of the TileButtons, adds them to the layout
    for (int i = 0; i < 32; i++)
    {
        layout->addWidget(board->tiles[i], i/4,(i - ((i/4)*4))*2 + (i/4)%2);
    }
    layout->addWidget(one,9,0);
    layout->addWidget(two,9,1);
    layout->addWidget(three,9,2);
    layout->addWidget(four,9,3);
    layout->addWidget(five,9,4);
    layout->addWidget(six,9,5);
    layout->addWidget(seven,9,6);
    layout->addWidget(eight,9,7);
    layout->addWidget(a,0,8);
    layout->addWidget(bb,1,8);
    layout->addWidget(c,2,8);
    layout->addWidget(d,3,8);
    layout->addWidget(e,4,8);
    layout->addWidget(f,5,8);
    layout->addWidget(g,6,8);
    layout->addWidget(h,7,8);

    QObject::connect(reset,SIGNAL(clicked(bool)),board, SLOT(resetBoard()));
    QObject::connect(this,SIGNAL(newGame()), board, SLOT(resetBoard()));
}

void MainWindow::updateLastMove(QString player, QString enemy)
{
    redLabel->setText("Red: " + player);
    blackLabel->setText("Black: " + enemy);
}
void MainWindow::showMenu()
{
    //this->hide();
    menu->show();
}
void MainWindow::resetB()
{
    emit newGame();
}
