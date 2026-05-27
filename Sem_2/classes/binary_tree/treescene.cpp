#include "treescene.h"
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QtMath>
#include <QCursor>

DraggableNode::DraggableNode(double value, QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent), nodeValue(value), label(nullptr)
{
    setRect(-20, -20, 40, 40);
    setBrush(QBrush(Qt::lightGray));
    setPen(QPen(Qt::black, 2));
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setCursor(QCursor(Qt::OpenHandCursor));
    setZValue(1);
}

void DraggableNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    dragStart = pos();
    setCursor(QCursor(Qt::ClosedHandCursor));
    QGraphicsEllipseItem::mousePressEvent(event);
}

void DraggableNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsEllipseItem::mouseMoveEvent(event);
    updateLabelPosition();
    if (scene()) {
        TreeScene *ts = dynamic_cast<TreeScene*>(scene());
        if (ts) ts->updateEdges();
    }
}

void DraggableNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(QCursor(Qt::OpenHandCursor));
    QGraphicsEllipseItem::mouseReleaseEvent(event);
}

void DraggableNode::updateLabelPosition()
{
    if (label) {
        label->setPos(pos().x() - 15, pos().y() - 15);
    }
}

TreeScene::TreeScene(BinaryTree *tree, QObject *parent) : QGraphicsScene(parent), t(tree)
{
    setSceneRect(0, 0, 1000, 700);
}

void TreeScene::updateTree()
{
    for (auto item : nodeItems) delete item;
    for (auto item : labelItems) delete item;
    for (auto item : edgeItems) delete item;
    nodeItems.clear();
    labelItems.clear();
    edgeItems.clear();
    savedPositions.clear();

    if (!t->getRoot()) return;

    int minX = 0, maxX = 0;
    layoutTree(t->getRoot(), 0, 500, minX, maxX);

    int offsetX = 0;
    if (minX < 0) offsetX = -minX + 50;

    QMap<TreeNode*, QPointF> adjustedPositions;
    for (auto it = savedPositions.begin(); it != savedPositions.end(); ++it) {
        adjustedPositions[it.key()] = QPointF(it.value().x() + offsetX, it.value().y());
    }
    savedPositions = adjustedPositions;

    for (auto it = savedPositions.begin(); it != savedPositions.end(); ++it) {
        TreeNode* node = it.key();
        QPointF pos = it.value();

        DraggableNode *circle = new DraggableNode(node->data);
        circle->setPos(pos);
        addItem(circle);
        nodeItems[node] = circle;

        QGraphicsTextItem *label = addText(QString::number(node->data));
        label->setFont(QFont("Arial", 10, QFont::Bold));
        label->setDefaultTextColor(Qt::black);
        label->setPos(pos.x() - 15, pos.y() - 15);
        label->setZValue(2);
        labelItems[node] = label;
        circle->setLabel(label);
    }

    updateEdges();
}

void TreeScene::layoutTree(TreeNode* node, int level, int x, int& minX, int& maxX)
{
    if (!node) return;

    int y = 50 + level * 80;
    savedPositions[node] = QPointF(x, y);

    if (x < minX) minX = x;
    if (x > maxX) maxX = x;

    int offset = 120 / (level + 1);
    if (offset < 30) offset = 30;

    if (node->left) {
        layoutTree(node->left, level + 1, x - offset, minX, maxX);
    }
    if (node->right) {
        layoutTree(node->right, level + 1, x + offset, minX, maxX);
    }
}

void TreeScene::updateEdges()
{
    for (auto item : edgeItems) delete item;
    edgeItems.clear();

    for (auto it = savedPositions.begin(); it != savedPositions.end(); ++it) {
        TreeNode* node = it.key();
        QPointF from = it.value();

        if (node->left && savedPositions.contains(node->left)) {
            QPointF to = savedPositions[node->left];
            QGraphicsLineItem *line = addLine(from.x(), from.y(), to.x(), to.y(), QPen(Qt::blue, 2));
            edgeItems.append(line);
        }
        if (node->right && savedPositions.contains(node->right)) {
            QPointF to = savedPositions[node->right];
            QGraphicsLineItem *line = addLine(from.x(), from.y(), to.x(), to.y(), QPen(Qt::blue, 2));
            edgeItems.append(line);
        }
    }
}
