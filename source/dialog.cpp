#include "dialog.h"

Dialog::Dialog(QWidget* parent)
{
    QFormLayout form(this);
    QList<QLineEdit*> fields;

    form.addRow(QString("Add new person"), );

    QLineEdit* lineEdit = new QLineEdit(this);
    form.addRow(QString("Firstname"), lineEdit);
    fields << lineEdit;

    lineEdit = new QLineEdit(this);
    form.addRow(QString("lastname"), lineEdit);
    fields << lineEdit;

    lineEdit = new QLineEdit(this);
    form.addRow(QString("city"), lineEdit);
    fields << lineEdit;

    lineEdit = new QLineEdit(this);
    form.addRow(QString("street"), lineEdit);
    fields << lineEdit;

    lineEdit = new QLineEdit(this);
    form.addRow(QString("house number"), lineEdit);
    fields << lineEdit;

    lineEdit = new QLineEdit(this);
    form.addRow(QString("age"), lineEdit);
    fields << lineEdit;

    lineEdit = new QLineEdit(this);
    form.addRow(QString("workplace"), lineEdit);
    fields << lineEdit;

    lineEdit = new QLineEdit(this);
    form.addRow(QString("hobby"), lineEdit);
    fields << lineEdit;

    lineEdit = new QLineEdit(this);
    form.addRow(QString("friends"), lineEdit);
    fields << lineEdit;

    this->exec( );
}