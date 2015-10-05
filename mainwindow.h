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

    QPlainTextEdit *tabSheet;

    void createActions();
    void createMenus();

    QAction *exitAction;

    QMenu *fileMenu;
};

#endif // MAINWINDOW_H
