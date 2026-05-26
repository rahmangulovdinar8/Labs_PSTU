#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QDialogButtonBox>
#include "item.h"


class ItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ItemDialog(QWidget *parent = nullptr);

    Item getItem() const;
    void setItem(const Item &item);

private slots:
    void onAccepted();

private:
    QLineEdit        *nameEdit;
    QPlainTextEdit   *descriptionEdit;
    QLineEdit        *ownerEdit;
    QLineEdit        *roomEdit;
    QComboBox        *categoryCombo;
    QLineEdit        *wantEdit;
    QDialogButtonBox *buttonBox;

    int m_editId = -1;
};

#endif // ITEMDIALOG_H
