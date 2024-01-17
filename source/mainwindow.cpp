#include "mainwindow.h"

MainWindow::MainWindow(QVector<Person*>* data, QWidget* parent) : QMainWindow(parent)
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

    contentsWindow->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, contentsWindow);

    headingTable = new QTableWidget(contentsWindow);
    headingTable->setRowCount(8);
    headingTable->setColumnCount(2);
    headingTable->verticalHeader( )->setVisible(false);
    headingTable->horizontalHeader( )->setVisible(false);
    headingTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    contentsWindow->setWidget(headingTable);

    headingTable->setItem(0, 0, new QTableWidgetItem(tr("name")));
    headingTable->setItem(1, 0, new QTableWidgetItem(tr("city")));
    headingTable->setItem(2, 0, new QTableWidgetItem(tr("street")));
    headingTable->setItem(3, 0, new QTableWidgetItem(tr("house number")));
    headingTable->setItem(4, 0, new QTableWidgetItem(tr("age")));
    headingTable->setItem(5, 0, new QTableWidgetItem(tr("workplace")));
    headingTable->setItem(6, 0, new QTableWidgetItem(tr("sex")));

    //for (auto j : node->getLinkedPerson( )->hobby)
    //{
    //    auto item5 = new QTableWidgetItem(tr(j.c_str( )));
    //}
    headingTable->setItem(0, 1, new QTableWidgetItem(tr(" ")));
    headingTable->setItem(1, 1, new QTableWidgetItem(tr(" ")));
    headingTable->setItem(2, 1, new QTableWidgetItem(tr(" ")));
    headingTable->setItem(3, 1, new QTableWidgetItem(tr(" ")));
    headingTable->setItem(4, 1, new QTableWidgetItem(tr(" ")));
    headingTable->setItem(5, 1, new QTableWidgetItem(tr(" ")));
    headingTable->setItem(6, 1, new QTableWidgetItem(tr(" ")));

    QDockWidget* linksWindow = new QDockWidget(tr("Links"), this);
    linksWindow->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    linksList = new QListWidget(linksWindow);
    addDockWidget(Qt::RightDockWidgetArea, linksWindow);

    linksWindow->setWidget(linksList);

    QWidget* centralWidget = new GraphWidget(data);
    setCentralWidget(centralWidget);

    auto connectionsWindow = new QDockWidget(tr("Table of Connections"), this);
    connectionsWindow->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, connectionsWindow);

    connectionsTable = new QTableWidget(connectionsWindow);
    connectionsTable->setRowCount(5);
    connectionsTable->setColumnCount(2);
    connectionsTable->verticalHeader( )->setVisible(false);
    connectionsTable->horizontalHeader( )->setVisible(false);
    connectionsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connectionsWindow->setWidget(connectionsTable);

    connectionsTable->setItem(0, 0, new QTableWidgetItem(tr("lastname")));
    connectionsTable->setItem(1, 0, new QTableWidgetItem(tr("city")));
    connectionsTable->setItem(2, 0, new QTableWidgetItem(tr("street")));
    connectionsTable->setItem(3, 0, new QTableWidgetItem(tr("house number")));
    connectionsTable->setItem(4, 0, new QTableWidgetItem(tr("workplace")));

    connectionsTable->setItem(0, 1, new QTableWidgetItem(tr(" ")));
    connectionsTable->setItem(1, 1, new QTableWidgetItem(tr(" ")));
    connectionsTable->setItem(2, 1, new QTableWidgetItem(tr(" ")));
    connectionsTable->setItem(3, 1, new QTableWidgetItem(tr(" ")));
    connectionsTable->setItem(4, 1, new QTableWidgetItem(tr(" ")));
}

void MainWindow::add( )
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Text files (*.txt)"));

    personList = new QVector<Person*>;
    DataInput::getData(personList, fileName.toStdString( ));
    auto temp = centralWidget( );
    QWidget* centralWidget = new GraphWidget(personList, this);
    setCentralWidget(centralWidget);
    delete temp;
}

void MainWindow::newGraph( )
{

    delete personList;
    add( );
}

void MainWindow::connectionsUpdate(QListWidgetItem* item)
{
    Person* itemPerson;
    for (auto i : activatedNode->getLinkedPerson( )->friends)
    {
        if (item->text( ).toStdString( ) == i->getData( ))
        {
            itemPerson = i;
            break;
        }
    }

    if (item->text( ).toStdString( ).substr(item->text( ).toStdString( ).find(' ') + 1, string::npos) == activatedNode->getLinkedPerson( )->lastname)
    {
        connectionsTable->item(0, 1)->setText(tr("true"));
    }
    else
    {
        connectionsTable->item(0, 1)->setText(tr("false"));
    }
    if (itemPerson->city == activatedNode->getLinkedPerson( )->city)
    {
        connectionsTable->item(1, 1)->setText(tr("true"));
    }
    else
    {
        connectionsTable->item(1, 1)->setText(tr("false"));
    }
    if (itemPerson->street == activatedNode->getLinkedPerson( )->street)
    {
        connectionsTable->item(2, 1)->setText(tr("true"));
    }
    else
    {
        connectionsTable->item(2, 1)->setText(tr("false"));
    }
    if (itemPerson->house_nr == activatedNode->getLinkedPerson( )->house_nr)
    {
        connectionsTable->item(3, 1)->setText(tr("true"));
    }
    else
    {
        connectionsTable->item(3, 1)->setText(tr("false"));
    }
    if (itemPerson->workplace == activatedNode->getLinkedPerson( )->workplace)
    {
        connectionsTable->item(4, 1)->setText(tr("true"));
    }
    else
    {
        connectionsTable->item(4, 1)->setText(tr("false"));
    }
}

void MainWindow::listUpdate(Node* node)
{

    headingTable->item(0, 1)->setText(tr(node->getLinkedPerson( )->getData( ).c_str( )));
    headingTable->item(1, 1)->setText(tr(node->getLinkedPerson( )->city.c_str( )));
    headingTable->item(2, 1)->setText(tr(node->getLinkedPerson( )->street.c_str( )));
    headingTable->item(3, 1)->setText(tr(node->getLinkedPerson( )->house_nr.c_str( )));
    headingTable->item(4, 1)->setText(tr((to_string(node->getLinkedPerson( )->age)).c_str( )));
    headingTable->item(5, 1)->setText(tr(node->getLinkedPerson( )->workplace.c_str( )));
    string sex = (node->getLinkedPerson( )->personSex == Person::sex::M ? "M" : "F");
    headingTable->item(6, 1)->setText(tr(sex.c_str( )));

    QSignalMapper* signalMapper = new QSignalMapper(this);
    linksList->clear( );

    for (auto i : node->getLinkedPerson( )->getFriends( ))
    {
        auto listItem = new QListWidgetItem(tr(i->getData( ).c_str( )), linksList);
        activatedNode = node;
        connect(linksList, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(connectionsUpdate(QListWidgetItem*)));
    }


}