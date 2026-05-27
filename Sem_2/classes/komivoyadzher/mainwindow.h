#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QTableWidget>
#include <QSpinBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSolve();
    void onLoadExample();
    void onClear();
    void onResize();

private:
    QTextEdit *output;
    QTableWidget *matrixTable;
    int n;
    QSpinBox *sizeSpin;
    void updateMatrixSize();
};

#endif
