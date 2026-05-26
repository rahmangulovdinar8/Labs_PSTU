#include "mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Lab2 - Graph Algorithms (Variant 9)");
    resize(1200, 800);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    QVBoxLayout *leftLayout = new QVBoxLayout();

    scene = new GraphScene(&g, this);
    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setSceneRect(0, 0, 800, 600);
    leftLayout->addWidget(view);

    QHBoxLayout *controlLayout = new QHBoxLayout();
    QPushButton *btnClear = new QPushButton("Clear");
    QPushButton *btnExample = new QPushButton("Load Example (Variant 9)");
    controlLayout->addWidget(btnClear);
    controlLayout->addWidget(btnExample);
    leftLayout->addLayout(controlLayout);
    mainLayout->addLayout(leftLayout, 2);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->setAlignment(Qt::AlignTop);

    QGroupBox *algoGroup = new QGroupBox("Algorithms");
    QVBoxLayout *algoLayout = new QVBoxLayout();
    QPushButton *btnBFS = new QPushButton("BFS (from vertex 3)");
    QPushButton *btnDFS = new QPushButton("DFS (from vertex 3)");
    QPushButton *btnDijkstra = new QPushButton("Dijkstra (from vertex 3)");
    QPushButton *btnFloyd = new QPushButton("Floyd (all pairs)");
    algoLayout->addWidget(btnBFS);
    algoLayout->addWidget(btnDFS);
    algoLayout->addWidget(btnDijkstra);
    algoLayout->addWidget(btnFloyd);
    algoGroup->setLayout(algoLayout);
    rightLayout->addWidget(algoGroup);

    QGroupBox *editGroup = new QGroupBox("Edit Graph");
    QVBoxLayout *editLayout = new QVBoxLayout();

    QHBoxLayout *vLayout = new QHBoxLayout();
    vertexInput = new QLineEdit();
    vertexInput->setPlaceholderText("Vertex name");
    QPushButton *btnAddVertex = new QPushButton("Add Vertex");
    QPushButton *btnRemoveVertex = new QPushButton("Remove Vertex");
    vLayout->addWidget(vertexInput);
    vLayout->addWidget(btnAddVertex);
    vLayout->addWidget(btnRemoveVertex);
    editLayout->addLayout(vLayout);

    QHBoxLayout *eLayout = new QHBoxLayout();
    edgeFrom = new QLineEdit();
    edgeFrom->setPlaceholderText("From");
    edgeTo = new QLineEdit();
    edgeTo->setPlaceholderText("To");
    weightInput = new QSpinBox();
    weightInput->setRange(1, 999);
    weightInput->setValue(10);
    QPushButton *btnAddEdge = new QPushButton("Add Edge");
    QPushButton *btnRemoveEdge = new QPushButton("Remove Edge");
    QPushButton *btnEditWeight = new QPushButton("Edit Weight");
    eLayout->addWidget(edgeFrom);
    eLayout->addWidget(edgeTo);
    eLayout->addWidget(weightInput);
    eLayout->addWidget(btnAddEdge);
    eLayout->addWidget(btnRemoveEdge);
    eLayout->addWidget(btnEditWeight);
    editLayout->addLayout(eLayout);

    editGroup->setLayout(editLayout);
    rightLayout->addWidget(editGroup);

    output = new QTextEdit();
    output->setReadOnly(true);
    output->setMaximumHeight(200);
    rightLayout->addWidget(new QLabel("Output:"));
    rightLayout->addWidget(output);

    mainLayout->addLayout(rightLayout, 1);

    connect(btnBFS, &QPushButton::clicked, this, &MainWindow::onBFS);
    connect(btnDFS, &QPushButton::clicked, this, &MainWindow::onDFS);
    connect(btnDijkstra, &QPushButton::clicked, this, &MainWindow::onDijkstra);
    connect(btnFloyd, &QPushButton::clicked, this, &MainWindow::onFloyd);
    connect(btnAddVertex, &QPushButton::clicked, this, &MainWindow::onAddVertex);
    connect(btnRemoveVertex, &QPushButton::clicked, this, &MainWindow::onRemoveVertex);
    connect(btnAddEdge, &QPushButton::clicked, this, &MainWindow::onAddEdge);
    connect(btnRemoveEdge, &QPushButton::clicked, this, &MainWindow::onRemoveEdge);
    connect(btnEditWeight, &QPushButton::clicked, this, &MainWindow::onEditWeight);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::onClear);
    connect(btnExample, &QPushButton::clicked, this, &MainWindow::onLoadExample);
}

MainWindow::~MainWindow() {}

void MainWindow::onLoadExample()
{
    g.clear();
    g.addVertex("1");
    g.addVertex("2");
    g.addVertex("3");
    g.addVertex("4");
    g.addVertex("5");
    g.addVertex("6");

    g.addEdge("1", "2", 3);
    g.addEdge("1", "5", 6);
    g.addEdge("2", "4", 27);
    g.addEdge("3", "4", 15);
    g.addEdge("3", "5", 9);
    g.addEdge("4", "3", 15);
    g.addEdge("4", "6", 12);
    g.addEdge("5", "2", 18);
    g.addEdge("5", "3", 9);
    g.addEdge("6", "3", 19);

    scene->updateGraph();
    output->append("Loaded example graph (Variant 9 F9 - directed)");
    output->append("Vertices: 1,2,3,4,5,6");
    output->append("Edges: 1->2(3), 1->5(6), 2->4(27), 3->4(15), 3->5(9), 4->3(15), 4->6(12), 5->2(18), 5->3(9), 6->3(19)");
    output->append("Bidirectional: 3<->4, 3<->5");
}

void MainWindow::onClear()
{
    g.clear();
    scene->updateGraph();
    output->append("Graph cleared");
}

void MainWindow::onAddVertex()
{
    QString name = vertexInput->text();
    if (!name.isEmpty()) {
        if (g.addVertex(name.toStdString())) {
            scene->updateGraph();
            output->append("Added vertex: " + name);
        } else {
            output->append("Vertex already exists: " + name);
        }
    }
}

void MainWindow::onRemoveVertex()
{
    QString name = vertexInput->text();
    if (!name.isEmpty()) {
        if (g.removeVertex(name.toStdString())) {
            scene->updateGraph();
            output->append("Removed vertex: " + name);
        } else {
            output->append("Vertex not found: " + name);
        }
    }
}

void MainWindow::onAddEdge()
{
    QString from = edgeFrom->text();
    QString to = edgeTo->text();
    int w = weightInput->value();
    if (!from.isEmpty() && !to.isEmpty()) {
        if (g.addEdge(from.toStdString(), to.toStdString(), w)) {
            scene->updateGraph();
            output->append(QString("Added edge: %1 -> %2 (weight=%3)").arg(from).arg(to).arg(w));
        } else {
            output->append("Edge already exists or vertices missing");
        }
    }
}

void MainWindow::onRemoveEdge()
{
    QString from = edgeFrom->text();
    QString to = edgeTo->text();
    if (!from.isEmpty() && !to.isEmpty()) {
        if (g.removeEdge(from.toStdString(), to.toStdString())) {
            scene->updateGraph();
            output->append("Removed edge: " + from + " -> " + to);
        } else {
            output->append("Edge not found");
        }
    }
}

void MainWindow::onEditWeight()
{
    QString from = edgeFrom->text();
    QString to = edgeTo->text();
    int w = weightInput->value();
    if (!from.isEmpty() && !to.isEmpty()) {
        if (g.setWeight(from.toStdString(), to.toStdString(), w)) {
            scene->updateGraph();
            output->append(QString("Updated weight: %1 -> %2 = %3").arg(from).arg(to).arg(w));
        } else {
            output->append("Edge not found");
        }
    }
}

void MainWindow::onBFS()
{
    std::vector<std::string> order = g.bfs("3");
    QString res = "BFS from vertex 3: ";
    for (const auto &v : order) res += QString::fromStdString(v) + " ";
    output->append(res);
}

void MainWindow::onDFS()
{
    std::vector<std::string> order = g.dfs("3");
    QString res = "DFS from vertex 3: ";
    for (const auto &v : order) res += QString::fromStdString(v) + " ";
    output->append(res);
}

void MainWindow::onDijkstra()
{
    auto distances = g.dijkstra("3");
    QString res = "Dijkstra from vertex 3:\n";
    for (const auto &pair : distances) {
        res += QString::fromStdString(pair.first) + ": " + QString::number(pair.second) + "  ";
    }
    output->append(res);
}

void MainWindow::onFloyd()
{
    auto dist = g.floyd();
    const auto &vertices = g.getVertices();
    output->append("Floyd-Warshall (shortest paths):");
    for (size_t i = 0; i < dist.size(); ++i) {
        QString line = QString::fromStdString(vertices[i]) + ": ";
        for (size_t j = 0; j < dist[i].size(); ++j) {
            if (dist[i][j] >= Graph::INF/2) line += "INF ";
            else line += QString::number(dist[i][j]) + " ";
        }
        output->append(line);
    }
}
