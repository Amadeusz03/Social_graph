#include <QMainWindow>
#include <QWidget>
#include <QMenuBar>
#include <QFile>
#include <QToolBar>
#include <QDockWidget>
#include <QListWidget>
#include <string>
#include <QLineEdit>
#include <QInputDialog>

#include "list.h"
#include "person.h"
#include "graphwidget.h"
#include "datainput.h"

class MainWindow : public QMainWindow
{
public:
    MainWindow(pro::list<Person>& data, QWidget* parent = nullptr);
    void open( );
};