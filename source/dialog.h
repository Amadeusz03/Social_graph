#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <string>

class Dialog : public QDialog
{
    Q_OBJECT

private:
    QList<QLineEdit*> fields;

public:
    Dialog(QWidget* parent = nullptr);
    static QStringList getStrings(QWidget* parent, bool* ok);
};

#endif // !DIALOG_H