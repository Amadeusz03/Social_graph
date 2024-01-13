#include "mainwindow.h"

MainWindow::MainWindow(pro::list<Person>& data, QWidget* parent) : QMainWindow(parent)
{
    //ddauto newAct = new QAction(tr("&New"), this);
    //newAct->setShortcuts(QKeySequence::New);
    //newAct->setStatusTip(tr("Create a new file"));
    //connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    auto openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    auto fileMenu = menuBar( )->addMenu(tr("&File"));
    //fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator( );

    auto fileToolBar = addToolBar(tr("File"));
    //fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    addToolBar(Qt::TopToolBarArea, fileToolBar);

    auto contentsWindow = new QDockWidget(tr("Table of Contents"), this);
    contentsWindow->setAllowedAreas(Qt::LeftDockWidgetArea
                                    | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, contentsWindow);

    auto headingList = new QListWidget(contentsWindow);
    contentsWindow->setWidget(headingList);

    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
    QWidget* centralWidget = new GraphWidget(data);
    setCentralWidget(centralWidget);
    menuBar( );
}

void MainWindow::open( )
{
    pro::list<Person> graphPerson;

    DataInput input;
    bool ok;
    QString text = QInputDialog::getText(this, tr("Label dialog"),
                                         tr("Enter path to file"),
                                         QLineEdit::Normal, "", &ok);
    input.getData(graphPerson, text.toStdString( ));
    QWidget* centralWidget = new GraphWidget(graphPerson);
    setCentralWidget(centralWidget);
}