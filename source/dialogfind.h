#ifndef DIALOGFIND_H
#define DIALOGFIND_H

#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <string>

class DialogFind : public QDialog
{
    Q_OBJECT

private:
    QList<QLineEdit*> fields;

public:
    DialogFind(QWidget* parent = nullptr);
    static QStringList getStrings(QWidget* parent, bool* ok);
};

#endif