#include "dialogfind.h"

DialogFind::DialogFind(QWidget* parent)
{
    auto form = new QFormLayout(this);

    form->addRow(new QLabel("Find person"));

    QLineEdit* lineEdit = new QLineEdit(this);
    form->addRow(QString("Firstname"), lineEdit);
    fields << lineEdit;

    lineEdit = new QLineEdit(this);
    form->addRow(QString("Lastname"), lineEdit);
    fields << lineEdit;

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    form->addRow(buttonBox);

    connect(buttonBox, SIGNAL(accepted( )), this, SLOT(accept( )));
    connect(buttonBox, SIGNAL(rejected( )), this, SLOT(reject( )));
}

QStringList DialogFind::getStrings(QWidget* parent, bool* ok)
{
    DialogFind* dialog = new DialogFind(parent);

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