#include "mainwindow.h"
#include "tsp.h"
#include <QString>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), n(6)
{
    setWindowTitle("Lab3 - Travelling Salesman Problem (Variant 9 - Custom Graph)");
    resize(850, 700);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    QGroupBox *matrixGroup = new QGroupBox("Cost Matrix");
    QVBoxLayout *matrixLayout = new QVBoxLayout(matrixGroup);

    QHBoxLayout *sizeLayout = new QHBoxLayout();
    sizeLayout->addWidget(new QLabel("Number of cities:"));
    sizeSpin = new QSpinBox();
    sizeSpin->setRange(3, 10);
    sizeSpin->setValue(6);
    QPushButton *btnResize = new QPushButton("Resize");
    sizeLayout->addWidget(sizeSpin);
    sizeLayout->addWidget(btnResize);
    matrixLayout->addLayout(sizeLayout);

    matrixTable = new QTableWidget(n, n);
    QStringList headers;
    for (int i = 1; i <= n; i++) headers << QString::number(i);
    matrixTable->setHorizontalHeaderLabels(headers);
    matrixTable->setVerticalHeaderLabels(headers);
    matrixTable->resizeColumnsToContents();
    matrixLayout->addWidget(matrixTable);
    mainLayout->addWidget(matrixGroup);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *btnLoadExample = new QPushButton("Load Custom Graph (6 cities)");
    QPushButton *btnClear = new QPushButton("Clear Matrix");
    QPushButton *btnSolve = new QPushButton("Solve TSP");
    buttonLayout->addWidget(btnLoadExample);
    buttonLayout->addWidget(btnClear);
    buttonLayout->addWidget(btnSolve);
    mainLayout->addLayout(buttonLayout);

    output = new QTextEdit();
    output->setReadOnly(true);
    output->setMaximumHeight(200);
    mainLayout->addWidget(new QLabel("Output:"));
    mainLayout->addWidget(output);

    connect(btnResize, &QPushButton::clicked, this, &MainWindow::onResize);
    connect(btnLoadExample, &QPushButton::clicked, this, &MainWindow::onLoadExample);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::onClear);
    connect(btnSolve, &QPushButton::clicked, this, &MainWindow::onSolve);

    onLoadExample();
}

MainWindow::~MainWindow() {}

void MainWindow::onResize()
{
    n = sizeSpin->value();
    matrixTable->setRowCount(n);
    matrixTable->setColumnCount(n);
    QStringList headers;
    for (int i = 1; i <= n; i++) headers << QString::number(i);
    matrixTable->setHorizontalHeaderLabels(headers);
    matrixTable->setVerticalHeaderLabels(headers);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                if (!matrixTable->item(i, j)) {
                    matrixTable->setItem(i, j, new QTableWidgetItem("INF"));
                }
            } else {
                if (!matrixTable->item(i, j)) {
                    matrixTable->setItem(i, j, new QTableWidgetItem("0"));
                }
            }
        }
    }
    matrixTable->resizeColumnsToContents();
    output->append("Resized matrix to " + QString::number(n) + "x" + QString::number(n));
}

void MainWindow::onLoadExample()
{
    n = 6;
    sizeSpin->setValue(6);
    matrixTable->setRowCount(6);
    matrixTable->setColumnCount(6);
    QStringList headers = {"1", "2", "3", "4", "5", "6"};
    matrixTable->setHorizontalHeaderLabels(headers);
    matrixTable->setVerticalHeaderLabels(headers);

    std::vector<std::vector<int>> example = {
        {TSP::INF, 12, 25, 18, 30, 42},
        {12, TSP::INF, 20, 14, 28, 35},
        {25, 20, TSP::INF, 16, 22, 38},
        {18, 14, 16, TSP::INF, 24, 30},
        {30, 28, 22, 24, TSP::INF, 26},
        {42, 35, 38, 30, 26, TSP::INF}
    };

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (example[i][j] >= TSP::INF / 2) {
                matrixTable->setItem(i, j, new QTableWidgetItem("INF"));
            } else {
                matrixTable->setItem(i, j, new QTableWidgetItem(QString::number(example[i][j])));
            }
        }
    }
    matrixTable->resizeColumnsToContents();
    output->append("Loaded custom graph (6 cities, symmetric)");
    output->append("Cities are fully connected");
}

void MainWindow::onClear()
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                matrixTable->setItem(i, j, new QTableWidgetItem("INF"));
            } else {
                matrixTable->setItem(i, j, new QTableWidgetItem("0"));
            }
        }
    }
    output->append("Matrix cleared");
}

void MainWindow::onSolve()
{
    std::vector<std::vector<int>> cost(n, std::vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            QTableWidgetItem *item = matrixTable->item(i, j);
            if (!item) {
                if (i == j) {
                    cost[i][j] = TSP::INF;
                } else {
                    cost[i][j] = 0;
                }
                continue;
            }
            QString text = item->text();
            if (text == "INF" || text == "") {
                cost[i][j] = TSP::INF;
            } else {
                bool ok;
                int val = text.toInt(&ok);
                if (ok) {
                    cost[i][j] = val;
                } else {
                    cost[i][j] = TSP::INF;
                }
            }
        }
    }

    TSP tsp(cost);
    auto result = tsp.solve();
    int totalCost = result.first;
    std::vector<int> path = result.second;

    if (totalCost >= TSP::INF / 2) {
        output->append("No valid Hamiltonian cycle found!");
        return;
    }

    QString pathStr = "Route: ";
    for (int v : path) {
        pathStr += QString::number(v + 1) + " ";
    }

    output->append("=== Result ===");
    output->append(pathStr);
    output->append("Total distance: " + QString::number(totalCost));
    output->append("");
}
