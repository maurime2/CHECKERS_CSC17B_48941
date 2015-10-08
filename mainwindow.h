#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow();

private slots:

private:
    //bool okToContinue(); rename as "pendingSave"
    QPlainTextEdit *tabSheet;

    void createActions();
    void createMenus();

    QAction *exitAction;

    QMenu *fileMenu;
};

#endif // MAINWINDOW_H
