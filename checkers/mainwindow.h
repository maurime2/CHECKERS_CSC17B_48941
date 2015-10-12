#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow();

private slots:

    void newFile();
    void open();
    void save();
    void saveAs();

private:

    void createActions();
    void createMenus();
    void createStatusBar();
    bool askToSave();

    QLabel *tileLocationLabel;

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;

    QMenu *fileMenu;
};

#endif // MAINWINDOW_H
