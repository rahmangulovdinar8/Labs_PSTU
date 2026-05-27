#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QGraphicsView>
#include "treescene.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadExample();
    void onClear();
    void onAddNode();
    void onRemoveNode();
    void onFindNode();
    void onPreorder();
    void onInorder();
    void onPostorder();
    void onBalance();
    void onFindMax();

private:
    QGraphicsView *view;
    TreeScene *scene;
    QTextEdit *output;
    QLineEdit *nodeInput;
    BinaryTree tree;
};

#endif
