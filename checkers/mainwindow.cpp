#include <QAction>
#include <QMenuBar>
#include <QStatusBar>

#include "mainwindow.h"

MainWindow::MainWindow()
{
    createActions();
    createMenus();
    createStatusBar();
}

void MainWindow::createActions()
{
    newAction = new QAction(QIcon(":/images/New.png"), "New", this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip("Create a new game");
    connect(newAction, SIGNAL(triggered(bool)),
            this, SLOT(newFile()));

    openAction = new QAction(QIcon(":/images/Open.png"), "Open", this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip("Open an existing game file");
    connect(openAction, SIGNAL(triggered(bool)),
            this, SLOT(open()));

    saveAction = new QAction(QIcon(":/images/Save.png"), "Save", this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip("Save game to disk");
    connect(saveAction, SIGNAL(triggered(bool)),
            this, SLOT(save()));

    saveAsAction = new QAction(QIcon(":/images/SaveAs.png"), "Save As...", this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip("Save game under new file name");
    connect(saveAsAction, SIGNAL(triggered(bool)),
            this, SLOT(saveAs()));

    exitAction = new QAction("Exit", this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered(bool)),
            this, SLOT(close()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

}

void MainWindow::newFile()
{

}

void MainWindow::open()
{

}

void MainWindow::save()
{

}

void MainWindow::saveAs()
{

}

void MainWindow::createStatusBar()
{
    tileLocationLabel = new QLabel("Tile location not implemented");
    tileLocationLabel->setAlignment(Qt::AlignHCenter);
    tileLocationLabel->setMinimumSize(tileLocationLabel->sizeHint());

    statusBar()->addWidget(tileLocationLabel);
}
