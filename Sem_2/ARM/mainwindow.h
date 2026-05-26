#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QTextEdit>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QSplitter>
#include "Bartermodel.h"
#include "Trademanager.h"
#include "glwidget.h"
#include "chainfinder.h"
#include "storage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddItem();
    void onRemoveItem();
    void onMakeTrade();
    void onFindChains();
    void saveData();

protected:
    void closeEvent(QCloseEvent *event) override;
    void onItemSelectionChanged();
    void onTradeCompleted(TradeRecord record);
    void refreshGL();

private:
    void buildUI();
    void updateStats();

    // Виджеты
    QTableView   *tableView;
    QTextEdit    *detailsText;
    QListWidget  *historyList;
    QPushButton  *addButton;
    QPushButton  *removeButton;
    QPushButton  *tradeButton;
    QPushButton  *chainButton;   // поиск цепочек
    QLabel       *statsLabel;
    QLabel       *statusLabel;
    GLWidget     *glWidget;

    // Данные
    BarterModel  *m_model;
    TradeManager *m_tradeManager;
};

#endif // MAINWINDOW_H
