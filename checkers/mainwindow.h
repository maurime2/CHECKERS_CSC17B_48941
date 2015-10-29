


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QPlainTextEdit> //delete me

//#include "board.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow();

protected:

    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:

    void newGame();
    void open();
    bool save();
    bool saveAs();
    void about();
    void documentWasModified();

private:

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    //QPlainTextEdit *textEdit;
    QString curFile;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
};

#endif
