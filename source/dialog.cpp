#include "dialog.h"

Dialog::Dialog(QWidget* parent)
{
    auto form = new QFormLayout(this);

    form->addRow(new QLabel("Add new person"));

    QLineEdit* lineEdit = new QLineEdit(this);
    form->addRow(QString("Firstname"), lineEdit);
    fields << lineEdit;

    lineEdit = new QLineEdit(this);
    form->addRow(QString("lastname"), lineEdit);
    fields << lineEdit;

    lineEdit = new QLineEdit(this);
    form->addRow(QString("city"), lineEdit);
    fields << lineEdit;

    lineEdit = new QLineEdit(this);
    form->addRow(QString("street"), lineEdit);
    fields << lineEdit;

    lineEdit = new QLineEdit(this);
    form->addRow(QString("house number"), lineEdit);
    fields << lineEdit;

    lineEdit = new QLineEdit(this);
    form->addRow(QString("age"), lineEdit);
    fields << lineEdit;

    lineEdit = new QLineEdit(this);
    form->addRow(QString("workplace"), lineEdit);
    fields << lineEdit;

    lineEdit = new QLineEdit(this);
    form->addRow(QString("hobby"), lineEdit);
    fields << lineEdit;

    lineEdit = new QLineEdit(this);
    form->addRow(QString("friends"), lineEdit);
    fields << lineEdit;

    lineEdit = new QLineEdit(this);
    form->addRow(QString("sex"), lineEdit);
    fields << lineEdit;

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    form->addRow(buttonBox);

    connect(buttonBox, SIGNAL(accepted( )), this, SLOT(accept( )));
    connect(buttonBox, SIGNAL(rejected( )), this, SLOT(reject( )));
}

QStringList Dialog::getStrings(QWidget* parent, bool* ok)
{
    Dialog* dialog = new Dialog(parent);

    QStringList list;

    const int returned = dialog->exec( );
    if (ok)
    {
        *ok = !!returned;
    }

    if (returned)
    {
        foreach(auto field, dialog->fields)
        {
            list << field->text( );
        }
    }

    dialog->deleteLater( );

    return list;
}