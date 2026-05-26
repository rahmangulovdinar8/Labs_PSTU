#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QGraphicsPathItem>
#include <QMap>
#include <QPointF>
#include "graph.h"

class ArrowItem : public QGraphicsPathItem
{
public:
    ArrowItem(const QPointF &from, const QPointF &to, int weight, QGraphicsItem *parent = nullptr);
    void setPoints(const QPointF &from, const QPointF &to);
    void setWeight(int weight) { edgeWeight = weight; updateWeightText(); }

private:
    QPointF startPoint;
    QPointF endPoint;
    int edgeWeight;
    QGraphicsTextItem *weightText;
    void updateWeightText();
    void updateArrow();
};

class DraggableVertex : public QGraphicsEllipseItem
{
public:
    DraggableVertex(const QString &name, QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    QString getName() const { return vertexName; }
    void setLabel(QGraphicsTextItem *l) { label = l; }
    void updateLabelPosition();
    QPointF getCenter() const { return pos(); }

private:
    QString vertexName;
    QPointF dragStart;
    QGraphicsTextItem *label;
};

class GraphScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphScene(Graph *graph, QObject *parent = nullptr);
    void updateGraph();
    void updateEdges();

private:
    Graph *g;
    QMap<std::string, DraggableVertex*> vertexItems;
    QMap<std::string, QGraphicsTextItem*> labelItems;
    QList<ArrowItem*> arrowItems;

    QPointF getVertexPosition(const std::string &name);
    QMap<std::string, QPointF> savedPositions;
};

#endif
