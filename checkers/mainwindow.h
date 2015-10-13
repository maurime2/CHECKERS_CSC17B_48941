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

protected:

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
    bool checkIfSaved();
    void writeSettings();
    void readSettings();

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
