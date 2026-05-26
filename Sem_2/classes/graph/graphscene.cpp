#include "graphscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QtMath>
#include <QCursor>
#include <QPainterPath>

ArrowItem::ArrowItem(const QPointF &from, const QPointF &to, int weight, QGraphicsItem *parent)
    : QGraphicsPathItem(parent), startPoint(from), endPoint(to), edgeWeight(weight)
{
    setPen(QPen(Qt::blue, 2));
    setBrush(QBrush(Qt::blue));
    updateArrow();

    weightText = new QGraphicsTextItem(QString::number(weight), this);
    weightText->setFont(QFont("Arial", 10));
    weightText->setDefaultTextColor(Qt::red);
    weightText->setZValue(3);
    updateWeightText();
}

void ArrowItem::setPoints(const QPointF &from, const QPointF &to)
{
    startPoint = from;
    endPoint = to;
    updateArrow();
    updateWeightText();
}

void ArrowItem::updateWeightText()
{
    QPointF mid = (startPoint + endPoint) / 2;
    weightText->setPos(mid.x() - 8, mid.y() - 8);
}

void ArrowItem::updateArrow()
{
    QPainterPath path;

    double angle = atan2(endPoint.y() - startPoint.y(), endPoint.x() - startPoint.x());
    double arrowSize = 15.0;

    QPointF arrowEnd = endPoint;
    QPointF arrowStart = startPoint;

    double dx = endPoint.x() - startPoint.x();
    double dy = endPoint.y() - startPoint.y();
    double len = sqrt(dx*dx + dy*dy);
    if (len > 20) {
        arrowStart = QPointF(
            startPoint.x() + (20.0 / len) * dx,
            startPoint.y() + (20.0 / len) * dy
        );
        arrowEnd = QPointF(
            endPoint.x() - (20.0 / len) * dx,
            endPoint.y() - (20.0 / len) * dy
        );
    }

    path.moveTo(arrowStart);
    path.lineTo(arrowEnd);

    QPointF arrowPoint1 = arrowEnd - QPointF(arrowSize * cos(angle - M_PI/6), arrowSize * sin(angle - M_PI/6));
    QPointF arrowPoint2 = arrowEnd - QPointF(arrowSize * cos(angle + M_PI/6), arrowSize * sin(angle + M_PI/6));

    path.moveTo(arrowEnd);
    path.lineTo(arrowPoint1);
    path.moveTo(arrowEnd);
    path.lineTo(arrowPoint2);

    setPath(path);
}

DraggableVertex::DraggableVertex(const QString &name, QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent), vertexName(name), label(nullptr)
{
    setRect(-20, -20, 40, 40);
    setBrush(QBrush(Qt::lightGray));
    setPen(QPen(Qt::black, 2));
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setCursor(QCursor(Qt::OpenHandCursor));
    setZValue(2);
}

void DraggableVertex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    dragStart = pos();
    setCursor(QCursor(Qt::ClosedHandCursor));
    QGraphicsEllipseItem::mousePressEvent(event);
}

void DraggableVertex::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsEllipseItem::mouseMoveEvent(event);
    updateLabelPosition();
    if (scene()) {
        GraphScene *gs = dynamic_cast<GraphScene*>(scene());
        if (gs) gs->updateEdges();
    }
}

void DraggableVertex::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(QCursor(Qt::OpenHandCursor));
    QGraphicsEllipseItem::mouseReleaseEvent(event);
}

void DraggableVertex::updateLabelPosition()
{
    if (label) {
        label->setPos(pos().x() - 10, pos().y() - 10);
    }
}

GraphScene::GraphScene(Graph *graph, QObject *parent) : QGraphicsScene(parent), g(graph)
{
    setSceneRect(0, 0, 800, 600);
}

void GraphScene::updateGraph()
{
    for (auto item : vertexItems) delete item;
    for (auto item : labelItems) delete item;
    for (auto item : arrowItems) delete item;
    vertexItems.clear();
    labelItems.clear();
    arrowItems.clear();

    const auto &vertices = g->getVertices();
    int n = vertices.size();
    if (n == 0) return;

    for (size_t i = 0; i < vertices.size(); ++i) {
        const std::string &v = vertices[i];
        QPointF pos;
        if (savedPositions.contains(v)) {
            pos = savedPositions[v];
        } else {
            double angle = 2 * M_PI * i / n;
            pos = QPointF(400 + 200 * cos(angle), 300 + 200 * sin(angle));
            savedPositions[v] = pos;
        }

        DraggableVertex *vertex = new DraggableVertex(QString::fromStdString(v));
        vertex->setPos(pos);
        addItem(vertex);
        vertexItems[v] = vertex;

        QGraphicsTextItem *label = addText(QString::fromStdString(v));
        label->setFont(QFont("Arial", 12, QFont::Bold));
        label->setDefaultTextColor(Qt::black);
        label->setPos(pos.x() - 10, pos.y() - 10);
        label->setZValue(3);
        labelItems[v] = label;
        vertex->setLabel(label);
    }

    updateEdges();
}

void GraphScene::updateEdges()
{
    for (auto item : arrowItems) delete item;
    arrowItems.clear();

    const auto &vertices = g->getVertices();

    for (size_t i = 0; i < vertices.size(); ++i) {
        for (size_t j = 0; j < vertices.size(); ++j) {
            if (i == j) continue;
            int w = g->getWeight(vertices[i], vertices[j]);
            if (w < Graph::INF && w != 0) {
                QPointF p1 = getVertexPosition(vertices[i]);
                QPointF p2 = getVertexPosition(vertices[j]);

                ArrowItem *arrow = new ArrowItem(p1, p2, w);
                addItem(arrow);
                arrowItems.append(arrow);
            }
        }
    }
}

QPointF GraphScene::getVertexPosition(const std::string &name)
{
    if (vertexItems.contains(name)) {
        return vertexItems[name]->getCenter();
    }
    return QPointF(0, 0);
}
