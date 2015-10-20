#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>// delete. for demo only
#include <QLabel>

#include "startscreen.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow();

protected:

    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);

private slots:

    void newFile();
    void open();
    bool save();
    bool saveAs();
    void gameModified();

private:

    void createActions();
    void createMenus();
    void createStatusBar();
    bool checkToSaveGame();
    void writeSettings();
    void readSettings();

    //StartWindow *startWindow;
    QLabel *tileLocationLabel;
    QPlainTextEdit *textEdit; // will delete later. For demo only

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;

    QMenu *fileMenu;
};

#endif // MAINWINDOW_H
