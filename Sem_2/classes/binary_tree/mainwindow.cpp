#include "mainwindow.h"
#include <QString>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Lab1 - Binary Tree (Variant 9)");
    resize(1200, 800);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    QVBoxLayout *leftLayout = new QVBoxLayout();

    scene = new TreeScene(&tree, this);
    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setSceneRect(0, 0, 1000, 700);
    leftLayout->addWidget(view);
    mainLayout->addLayout(leftLayout, 2);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->setAlignment(Qt::AlignTop);

    QGroupBox *exampleGroup = new QGroupBox("Example");
    QVBoxLayout *exampleLayout = new QVBoxLayout();
    QPushButton *btnLoadExample = new QPushButton("Load Example (Variant 9)");
    QPushButton *btnClear = new QPushButton("Clear Tree");
    exampleLayout->addWidget(btnLoadExample);
    exampleLayout->addWidget(btnClear);
    exampleGroup->setLayout(exampleLayout);
    rightLayout->addWidget(exampleGroup);

    QGroupBox *editGroup = new QGroupBox("Edit Tree");
    QVBoxLayout *editLayout = new QVBoxLayout();
    QHBoxLayout *inputLayout = new QHBoxLayout();
    nodeInput = new QLineEdit();
    nodeInput->setPlaceholderText("Enter double value");
    QPushButton *btnAdd = new QPushButton("Add");
    QPushButton *btnRemove = new QPushButton("Remove");
    QPushButton *btnFind = new QPushButton("Find");
    inputLayout->addWidget(nodeInput);
    inputLayout->addWidget(btnAdd);
    inputLayout->addWidget(btnRemove);
    inputLayout->addWidget(btnFind);
    editLayout->addLayout(inputLayout);
    editGroup->setLayout(editLayout);
    rightLayout->addWidget(editGroup);

    QGroupBox *traversalGroup = new QGroupBox("Traversals");
    QVBoxLayout *traversalLayout = new QVBoxLayout();
    QPushButton *btnPreorder = new QPushButton("Preorder (Root-Left-Right)");
    QPushButton *btnInorder = new QPushButton("Inorder (Left-Root-Right)");
    QPushButton *btnPostorder = new QPushButton("Postorder (Left-Right-Root)");
    traversalLayout->addWidget(btnPreorder);
    traversalLayout->addWidget(btnInorder);
    traversalLayout->addWidget(btnPostorder);
    traversalGroup->setLayout(traversalLayout);
    rightLayout->addWidget(traversalGroup);

    QGroupBox *algoGroup = new QGroupBox("Algorithms");
    QVBoxLayout *algoLayout = new QVBoxLayout();
    QPushButton *btnBalance = new QPushButton("Balance Tree");
    QPushButton *btnFindMax = new QPushButton("Find Maximum Element");
    algoLayout->addWidget(btnBalance);
    algoLayout->addWidget(btnFindMax);
    algoGroup->setLayout(algoLayout);
    rightLayout->addWidget(algoGroup);

    output = new QTextEdit();
    output->setReadOnly(true);
    output->setMaximumHeight(200);
    rightLayout->addWidget(new QLabel("Output:"));
    rightLayout->addWidget(output);

    mainLayout->addLayout(rightLayout, 1);

    connect(btnLoadExample, &QPushButton::clicked, this, &MainWindow::onLoadExample);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::onClear);
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::onAddNode);
    connect(btnRemove, &QPushButton::clicked, this, &MainWindow::onRemoveNode);
    connect(btnFind, &QPushButton::clicked, this, &MainWindow::onFindNode);
    connect(btnPreorder, &QPushButton::clicked, this, &MainWindow::onPreorder);
    connect(btnInorder, &QPushButton::clicked, this, &MainWindow::onInorder);
    connect(btnPostorder, &QPushButton::clicked, this, &MainWindow::onPostorder);
    connect(btnBalance, &QPushButton::clicked, this, &MainWindow::onBalance);
    connect(btnFindMax, &QPushButton::clicked, this, &MainWindow::onFindMax);
}

MainWindow::~MainWindow() {}

void MainWindow::onLoadExample()
{
    tree.clear();
    std::vector<double> values = {5.5, 2.1, 8.9, 1.3, 9.4, 3.7, 6.2, 4.5, 7.8};
    for (double v : values) {
        tree.insert(v);
    }
    scene->updateTree();
    output->append("Loaded example tree with values: 5.5, 2.1, 8.9, 1.3, 9.4, 3.7, 6.2, 4.5, 7.8");
}

void MainWindow::onClear()
{
    tree.clear();
    scene->updateTree();
    output->append("Tree cleared");
}

void MainWindow::onAddNode()
{
    bool ok;
    double val = nodeInput->text().toDouble(&ok);
    if (ok) {
        tree.insert(val);
        scene->updateTree();
        output->append("Added node: " + QString::number(val));
    } else {
        output->append("Invalid input. Enter a number.");
    }
    nodeInput->clear();
}

void MainWindow::onRemoveNode()
{
    bool ok;
    double val = nodeInput->text().toDouble(&ok);
    if (ok) {
        if (tree.remove(val)) {
            scene->updateTree();
            output->append("Removed node: " + QString::number(val));
        } else {
            output->append("Node not found: " + QString::number(val));
        }
    } else {
        output->append("Invalid input. Enter a number.");
    }
    nodeInput->clear();
}

void MainWindow::onFindNode()
{
    bool ok;
    double val = nodeInput->text().toDouble(&ok);
    if (ok) {
        if (tree.find(val)) {
            output->append("Node found: " + QString::number(val));
        } else {
            output->append("Node not found: " + QString::number(val));
        }
    } else {
        output->append("Invalid input. Enter a number.");
    }
    nodeInput->clear();
}

void MainWindow::onPreorder()
{
    std::vector<double> result = tree.preorder();
    QString str = "Preorder: ";
    for (double v : result) str += QString::number(v) + " ";
    output->append(str);
}

void MainWindow::onInorder()
{
    std::vector<double> result = tree.inorder();
    QString str = "Inorder: ";
    for (double v : result) str += QString::number(v) + " ";
    output->append(str);
}

void MainWindow::onPostorder()
{
    std::vector<double> result = tree.postorder();
    QString str = "Postorder: ";
    for (double v : result) str += QString::number(v) + " ";
    output->append(str);
}

void MainWindow::onBalance()
{
    tree.balance();
    scene->updateTree();
    output->append("Tree balanced");
}

void MainWindow::onFindMax()
{
    double maxVal = tree.findMax();
    if (tree.getRoot() != nullptr) {
        output->append("Maximum element: " + QString::number(maxVal));
    } else {
        output->append("Tree is empty");
    }
}
