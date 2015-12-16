#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QLabel>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     MainWindow(QWidget *parent = 0);
    QLabel *redLabel;
    QLabel *blackLabel;
    QPushButton *reset;
private:

public slots:
     void updateLastMove(QString,QString);
};

#endif // MAINWINDOW_H
