#ifndef TREESCENE_H
#define TREESCENE_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QMap>
#include "tree.h"

class DraggableNode : public QGraphicsEllipseItem
{
public:
    DraggableNode(double value, QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    double getValue() const { return nodeValue; }
    void setLabel(QGraphicsTextItem *l) { label = l; }
    void updateLabelPosition();
    QPointF getCenter() const { return pos(); }

private:
    double nodeValue;
    QPointF dragStart;
    QGraphicsTextItem *label;
};

class TreeScene : public QGraphicsScene
{
    Q_OBJECT
public:
    TreeScene(BinaryTree *tree, QObject *parent = nullptr);
    void updateTree();
    void updateEdges();

private:
    BinaryTree *t;
    QMap<TreeNode*, DraggableNode*> nodeItems;
    QMap<TreeNode*, QGraphicsTextItem*> labelItems;
    QList<QGraphicsLineItem*> edgeItems;
    QMap<TreeNode*, QPointF> savedPositions;

    void layoutTree(TreeNode* node, int level, int x, int& minX, int& maxX);
    QPointF getNodePosition(TreeNode* node);
};

#endif
