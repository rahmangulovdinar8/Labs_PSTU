#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include "graphscene.h"
#include "graph.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onBFS();
    void onDFS();
    void onDijkstra();
    void onFloyd();
    void onAddVertex();
    void onRemoveVertex();
    void onAddEdge();
    void onRemoveEdge();
    void onEditWeight();
    void onClear();
    void onLoadExample();

private:
    QGraphicsView *view;
    GraphScene *scene;
    QTextEdit *output;
    QLineEdit *vertexInput;
    QLineEdit *edgeFrom;
    QLineEdit *edgeTo;
    QSpinBox *weightInput;
    Graph g;
};

#endif
