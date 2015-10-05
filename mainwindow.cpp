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
    exitAction = new QAction("Exit", this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered(bool)),
            this, SLOT(close()));
}

void MainWindow::createMenus()

{
    fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(exitAction);
}
