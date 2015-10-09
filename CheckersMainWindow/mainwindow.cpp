#include "mainwindow.h"

#include <QAction>
#include <QMenuBar>

MainWindow::MainWindow()
{
    tabSheet = new QPlainTextEdit();
    setCentralWidget(tabSheet);

    createActions();
    createMenus();
}

void MainWindow::createActions()
{
    newAction = new QAction(QIcon(":/images/New.png"), "New", this);
    newAction->setShortcut(QKeySequence::New);
    connect(newAction, SIGNAL(triggered(bool)),
            this, SLOT(newFile()));

    openAction = new QAction(QIcon(":/images/Open.png"), "Open", this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, SIGNAL(triggered(bool)),
            this, SLOT(open()));

    saveAction = new QAction(QIcon(":/images/Save.png"), "Save", this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, SIGNAL(triggered(bool)),
            this, SLOT(save()));

    saveAsAction = new QAction("Save As", this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
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
