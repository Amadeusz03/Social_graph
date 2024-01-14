#include "mainwindow.h"

QDockWidget* MainWindow::bar = nullptr;

MainWindow::MainWindow(QVector<Person>& data, QWidget* parent) : QMainWindow(parent)
{
    //ddauto newAct = new QAction(tr("&New"), this);
    //newAct->setShortcuts(QKeySequence::New);
    //newAct->setStatusTip(tr("Create a new file"));
    //connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    auto openAct = new QAction(tr("&Add"), this);
    openAct->setStatusTip(tr("Add person file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::add);

    auto newAct = new QAction(tr("&New"), this);
    openAct->setStatusTip(tr("Create new graph"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newGraph);

    auto fileMenu = menuBar( )->addMenu(tr("&File"));
    //fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(newAct);
    fileMenu->addSeparator( );

    auto fileToolBar = addToolBar(tr("File"));
    //fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(newAct);
    fileToolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    addToolBar(Qt::TopToolBarArea, fileToolBar);


    ///
    auto contentsWindow = new QDockWidget(tr("Table of Contents"), this);

    contentsWindow->setAllowedAreas(Qt::LeftDockWidgetArea
                                    | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, contentsWindow);

    auto headingList = new QListWidget(contentsWindow);
    contentsWindow->setWidget(headingList);
    bar = contentsWindow;


    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
    QWidget* centralWidget = new GraphWidget(data);
    setCentralWidget(centralWidget);
}

void MainWindow::add( )
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Text files (*.txt)"));

    DataInput::getData(personList, fileName.toStdString( ));
    auto temp = centralWidget( ); //! test later
    QWidget* centralWidget = new GraphWidget(personList);
    setCentralWidget(centralWidget);
    delete temp;
}

void MainWindow::newGraph( )
{
    personList.clear( );
    add( );
}

void MainWindow::listUpdate( )
{
    removeDockWidget(bar);

    auto contentsWindow = new QDockWidget(tr("Table of Contents"), this);

    bar = contentsWindow;
    contentsWindow->setAllowedAreas(Qt::LeftDockWidgetArea
                                    | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, contentsWindow);

    auto headingList = new QListWidget(contentsWindow);
    contentsWindow->setWidget(headingList);

    new QListWidgetItem(tr("Oak"), headingList);
    new QListWidgetItem(tr("Fir"), headingList);
    new QListWidgetItem(tr("Pine"), headingList);
}