#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QDialog>
#include <QPushButton>

class MenuDialog : public QDialog
{
    Q_OBJECT

public:

    MenuDialog(QWidget *parent = 0);

signals:

    void closeGame();
    void openGame();

private slots:

    void quitClicked();

private:

    QPushButton *newButton;
    QPushButton *continueButton;
    QPushButton *loadButton;
    QPushButton *quitButton;
    QPushButton *optionsButton;
};
#endif // MENUDIALOG_H
