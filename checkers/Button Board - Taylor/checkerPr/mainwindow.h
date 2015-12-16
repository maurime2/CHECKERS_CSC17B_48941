#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <menudialog.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     MainWindow(QWidget *parent = 0);
    QLabel *redLabel;
    QLabel *blackLabel;
    QPushButton *reset;
    MenuDialog *menu;
private:
signals:
    void newGame();
public slots:
     void updateLastMove(QString,QString);
     void showMenu();
     void resetB();
};

#endif // MAINWINDOW_H
