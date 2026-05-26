#ifndef CHAINDIALOG_H
#define CHAINDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QTabWidget>
#include "chainfinder.h"
#include "graphwidget.h"

class ChainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChainDialog(const QVector<BarterChain> &chains,
                         QWidget *parent = nullptr);

    int selectedChainIndex() const { return m_selectedIndex; }

private slots:
    void onChainSelected(int row);
    void onConfirm();

private:
    QVector<BarterChain> m_chains;
    QListWidget         *m_listWidget;
    QTextEdit           *m_detailText;
    GraphWidget         *m_graphWidget;
    QPushButton         *m_confirmBtn;
    int                  m_selectedIndex = -1;
};

#endif // CHAINDIALOG_H
