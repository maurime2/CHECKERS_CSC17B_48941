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

    void newFile();
    void open();
    void save();
    void saveAs();

private:
<<<<<<< HEAD:mainwindow.h

    QPlainTextEdit *tabSheet;
=======
>>>>>>> 61e74027b85458879f5362e8f5f1c3d4a58d8dba:checkers/mainwindow.h

    void createActions();
    void createMenus();
    bool pendingSave();

    QPlainTextEdit *tabSheet;

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;

    QMenu *fileMenu;
};

#endif // MAINWINDOW_H
