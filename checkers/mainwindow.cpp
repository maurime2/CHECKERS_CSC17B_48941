#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>
#include <QSplashScreen>

#include "mainwindow.h"
#include "startscreen.h"

MainWindow::MainWindow()
{
    textEdit = new QPlainTextEdit;
    setCentralWidget(textEdit);

    createActions();
    createMenus();
    createStatusBar();

    readSettings();

    connect(textEdit->document(), SIGNAL(contentsChanged()),
            this, SLOT(gameModified()));
}

void MainWindow::showEvent(QShowEvent *event)
{
    //startWindow = new StartWindow(this);

    //startWindow->show();
    //startWindow->raise();
    //startWindow->activateWindow();
}

void MainWindow::createActions()
{
    newAction = new QAction("&New", this);
    newAction->setIcon(QIcon(":/images/New.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip("Create a new game");
    connect(newAction, SIGNAL(triggered(bool)),
            this, SLOT(newFile()));

    openAction = new QAction("&Open", this);
    openAction->setIcon(QIcon(":/images/Open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip("Open an existing game file");
    connect(openAction, SIGNAL(triggered(bool)),
            this, SLOT(open()));

    saveAction = new QAction("&Save", this);
    saveAction->setIcon((QIcon(":/images/Save.png")));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip("Save game to disk");
    connect(saveAction, SIGNAL(triggered(bool)),
            this, SLOT(save()));

    saveAsAction = new QAction("Save &As...", this);
    saveAsAction->setIcon(QIcon(":/images/SaveAs.png"));
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip("Save game under new file name");
    connect(saveAsAction, SIGNAL(triggered(bool)),
            this, SLOT(saveAs()));

    exitAction = new QAction("E&xit", this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip("Exit the application");
    connect(exitAction, SIGNAL(triggered(bool)),
            this, SLOT(close()));
}

void MainWindow::createMenus()
{
    menuBar()->setNativeMenuBar(false);
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
}

void MainWindow::createStatusBar()
{
    tileLocationLabel = new QLabel("Tile location not implemented");
    tileLocationLabel->setAlignment(Qt::AlignHCenter);
    tileLocationLabel->setMinimumSize(tileLocationLabel->sizeHint());

    statusBar()->addWidget(tileLocationLabel);
}

void MainWindow::gameModified()
{
    setWindowModified(textEdit->document()->isModified());
}

bool MainWindow::checkToSaveGame()
{
    if (textEdit->document()->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Application"),
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::newFile()
{
    if (checkToSaveGame()) {
        textEdit->clear();
        //setCurrentFile("");
    }
}

void MainWindow::open()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (checkToSaveGame()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}


bool MainWindow::save()
{
    return true;
}

bool MainWindow::saveAs()
{
    return true;
}

void MainWindow::writeSettings()
{
    QSettings settings("The Checkers Group", "Checkers");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

void MainWindow::readSettings()
{
    QSettings settings("The Checkers Group", "Checkers");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}
