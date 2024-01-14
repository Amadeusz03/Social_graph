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
#include <QFileDialog>
#include <QVector>

#include "list.h"
#include "person.h"
#include "graphwidget.h"
#include "datainput.h"

class MainWindow : public QMainWindow
{
private:
    QVector<Person> personList;
public:
    MainWindow(QVector<Person>& data, QWidget* parent = nullptr);
    void add( );
    void newGraph( );
};