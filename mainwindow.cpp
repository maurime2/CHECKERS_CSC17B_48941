#include "mainwindow.h"

#include <QMenuBar>
#include <QAction>
#include <QToolBar>

MainWindow::MainWindow()
{
    createActions();
    createMenus();
    createToolBars();
    createContextMenu();
    createStatusBar();
}

void MainWindow::createActions()
{
    newAction = new QAction(tr("New"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    openAction = new QAction(("Open..."), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setChecked(true);
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(("Save"), this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAction = new QAction(("Save As..."), this);
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAction = new QAction(tr("Exit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

}

void MainWindow::createContextMenu()
{

}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar("File");
    fileToolBar->addAction(newAction);
}

void MainWindow::createStatusBar()
{

}

void MainWindow::newFile()
{

}







