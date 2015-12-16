#ifndef GAMEOVERDIALOG_H
#define GAMEOVERDIALOG_H

#include <QPushButton>
#include <QDialog>
class GameOverDialog : public QDialog
{
    Q_OBJECT
public:
    GameOverDialog(QWidget *parent = 0);
    QPushButton *playAgain;
    QPushButton *quit;
    QPushButton *mainMenu;

signals:

public slots:
    void winOrLoss(bool win);
};

#endif // GAMEOVERDIALOG_H
