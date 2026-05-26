#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>
#include <QVector>
#include <QMap>
#include <QtMath>
#include "chainfinder.h"

// Узел графа
struct GraphNode {
    int     itemId;
    QString ownerName;
    QString itemName;
    float   x, y;
    float   targetX, targetY;
    float   colorR, colorG, colorB;
};

// Ребро графа
struct GraphEdge {
    int fromItemId;
    int toItemId;
    bool highlighted; // подсвечено как часть выбранной цепочки
};

class GraphWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *parent = nullptr);

    // Загрузить все найденные цепочки
    void setChains(const QVector<BarterChain> &chains);

    // Подсветить конкретную цепочку
    void highlightChain(int chainIndex);

    // Очистить граф
    void clear();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    void buildGraph();
    void layoutNodes();   // расставить узлы по кругу
    void drawNode(const GraphNode &node, bool highlighted);
    void drawArrow(float x1, float y1, float x2, float y2,
                   float r, float g, float b, float alpha);
    void drawTextLabel(float x, float y, const QString &line1,
                       const QString &line2);

    // Анимация плавного появления
    QTimer *m_animTimer;
    float   m_animProgress; // 0..1

    QVector<GraphNode>  m_nodes;
    QVector<GraphEdge>  m_edges;
    QVector<BarterChain> m_chains;
    int                 m_highlightedChain; // -1 = все
    int                 m_highlightedChainLen; // длина выбранной цепочки

    QMap<int, int> m_nodeIndex;
};

#endif // GRAPHWIDGET_H
