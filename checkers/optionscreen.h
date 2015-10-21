#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>
#include <QPushButton>

#include "mainwindow.h"

class OptionScreen : public QDialog
{
public:

    OptionScreen(QWidget *parent = 0);

private:

    QPushButton *newButton;
    QPushButton *continueButton;
    QPushButton *loadButton;
    QPushButton *quitButton;
};

#endif // STARTWINDOW_H
