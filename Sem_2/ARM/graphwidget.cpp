#include "graphwidget.h"
#include <QPainter>
#include <QFont>
#include <cmath>

GraphWidget::GraphWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_animProgress(0.0f)
    , m_highlightedChain(-1)
    , m_highlightedChainLen(0)
{
    m_animTimer = new QTimer(this);
    connect(m_animTimer, &QTimer::timeout, this, [this](){
        m_animProgress += 0.03f;
        if (m_animProgress >= 1.0f) {
            m_animProgress = 1.0f;
            m_animTimer->stop();
        }
        update();
    });
    setMinimumHeight(300);
}

void GraphWidget::setChains(const QVector<BarterChain> &chains) {
    m_chains = chains;
    m_highlightedChain = -1;
    buildGraph();
    layoutNodes();
    m_animProgress = 0.0f;
    m_animTimer->start(16);
}

void GraphWidget::highlightChain(int chainIndex) {
    m_highlightedChain = chainIndex;
    m_highlightedChainLen = (chainIndex >= 0 && chainIndex < m_chains.size())
                             ? m_chains[chainIndex].length() : 0;

    for (GraphEdge &e : m_edges) e.highlighted = false;

    if (chainIndex >= 0 && chainIndex < m_chains.size()) {
        const BarterChain &chain = m_chains[chainIndex];
        for (const ChainStep &step : chain.steps) {
            for (GraphEdge &e : m_edges) {
                if (e.fromItemId == step.giverId && e.toItemId == step.takerId)
                    e.highlighted = true;
            }
        }
        layoutNodes();
    }

    m_animProgress = 0.0f;
    m_animTimer->start(16);
    update();
}

void GraphWidget::clear() {
    m_nodes.clear();
    m_edges.clear();
    m_chains.clear();
    m_highlightedChain = -1;
    update();
}

void GraphWidget::buildGraph() {
    m_nodes.clear();
    m_edges.clear();
    m_nodeIndex.clear();

    float chainColors[][3] = {
        {0.2f, 0.6f, 1.0f},
        {0.3f, 0.85f, 0.4f},
        {1.0f, 0.5f, 0.1f},
        {0.9f, 0.2f, 0.4f},
        {0.7f, 0.3f, 1.0f},
    };

    for (int ci = 0; ci < m_chains.size(); ++ci) {
        const BarterChain &chain = m_chains[ci];
        float r = chainColors[ci % 5][0];
        float g = chainColors[ci % 5][1];
        float b = chainColors[ci % 5][2];

        for (const ChainStep &step : chain.steps) {
            if (!m_nodeIndex.contains(step.giverId)) {
                GraphNode node;
                node.itemId    = step.giverId;
                node.ownerName = step.giverName;
                node.itemName  = step.itemName;
                node.x = node.targetX = 0;
                node.y = node.targetY = 0;
                node.colorR = r; node.colorG = g; node.colorB = b;
                m_nodeIndex[step.giverId] = m_nodes.size();
                m_nodes.append(node);
            }
            if (!m_nodeIndex.contains(step.takerId)) {
                GraphNode node;
                node.itemId    = step.takerId;
                node.ownerName = step.takerName;
                node.itemName  = "";
                node.x = node.targetX = 0;
                node.y = node.targetY = 0;
                node.colorR = r; node.colorG = g; node.colorB = b;
                m_nodeIndex[step.takerId] = m_nodes.size();
                m_nodes.append(node);
            }
            GraphEdge edge;
            edge.fromItemId  = step.giverId;
            edge.toItemId    = step.takerId;
            edge.highlighted = false;
            bool exists = false;
            for (const GraphEdge &ex : m_edges)
                if (ex.fromItemId == edge.fromItemId && ex.toItemId == edge.toItemId)
                { exists = true; break; }
            if (!exists) m_edges.append(edge);
        }
    }

    // Заполняем itemName получателей
    for (int i = 0; i < m_nodes.size(); ++i) {
        if (m_nodes[i].itemName.isEmpty()) {
            for (const BarterChain &c : m_chains)
                for (const ChainStep &s : c.steps)
                    if (s.giverId == m_nodes[i].itemId) {
                        m_nodes[i].itemName = s.itemName;
                        break;
                    }
        }
    }
}

void GraphWidget::layoutNodes() {
    int n = m_nodes.size();
    if (n == 0) return;

    if (m_highlightedChain >= 0 && m_highlightedChain < m_chains.size()) {
        const BarterChain &chain = m_chains[m_highlightedChain];


        QVector<int> chainIds;
        for (const ChainStep &s : chain.steps)
            if (!chainIds.contains(s.giverId))
                chainIds.append(s.giverId);

        int nc = chainIds.size();
        float mainR = 0.68f;


        for (int i = 0; i < nc; ++i) {
            // Идём по часовой: угол растёт в положительную сторону
            float angle = -M_PI / 2.0f + (2.0f * M_PI * i / nc);
            int idx = m_nodeIndex.value(chainIds[i], -1);
            if (idx < 0) continue;
            m_nodes[idx].targetX = mainR * cosf(angle);
            m_nodes[idx].targetY = mainR * sinf(angle);
        }

        // Остальные узлы компактно в правом нижнем углу
        int otherCount = 0;
        int otherTotal = 0;
        for (const GraphNode &nd : m_nodes)
            if (!chainIds.contains(nd.itemId)) otherTotal++;

        for (int i = 0; i < m_nodes.size(); ++i) {
            if (!chainIds.contains(m_nodes[i].itemId)) {
                float angle = 2.0f * M_PI * otherCount / qMax(1, otherTotal);
                m_nodes[i].targetX = 0.50f + 0.20f * cosf(angle);
                m_nodes[i].targetY = -0.55f + 0.20f * sinf(angle);
                otherCount++;
            }
        }
    } else {
        // Все узлы равномерно по кругу
        float mainR = 0.70f;
        for (int i = 0; i < n; ++i) {
            float angle = -M_PI / 2.0f + (2.0f * M_PI * i / n);
            m_nodes[i].x       = 0;
            m_nodes[i].y       = 0;
            m_nodes[i].targetX = mainR * cosf(angle);
            m_nodes[i].targetY = mainR * sinf(angle);
        }
    }
}

void GraphWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.10f, 0.10f, 0.16f, 1.0f);
}

void GraphWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (h > 0) ? float(w) / h : 1.0f;
    glOrtho(-aspect, aspect, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Стрелка: острие ВСЕГДА у получателя (x2,y2)
void GraphWidget::drawArrow(float x1, float y1, float x2, float y2,
                             float r, float g, float b, float alpha)
{
    float dx = x2 - x1, dy = y2 - y1;
    float len = sqrtf(dx*dx + dy*dy);
    if (len < 0.001f) return;

    float ux = dx / len, uy = dy / len;
    float nodeR    = 0.095f;
    float arrowLen = 0.060f;
    float arrowW   = 0.024f;

    // Линия: от края узла-отправителя до края узла-получателя
    float sx = x1 + ux * nodeR;
    float sy = y1 + uy * nodeR;
    float ex = x2 - ux * nodeR;          // конец линии (у получателя)
    float ey = y2 - uy * nodeR;

    glColor4f(r, g, b, alpha);
    glLineWidth(alpha > 0.5f ? 2.5f : 1.0f);
    glBegin(GL_LINES);
        glVertex2f(sx, sy);
        glVertex2f(ex, ey);
    glEnd();

    // Наконечник: острие = (ex,ey), основание отступает назад
    float bx = ex - ux * arrowLen;
    float by = ey - uy * arrowLen;
    float px = -uy * arrowW;   // перпендикуляр
    float py =  ux * arrowW;

    glBegin(GL_TRIANGLES);
        glVertex2f(ex,        ey);         // острие у получателя
        glVertex2f(bx + px,   by + py);
        glVertex2f(bx - px,   by - py);
    glEnd();
}

void GraphWidget::drawNode(const GraphNode &node, bool highlighted) {
    float nx = node.x, ny = node.y;
    float radius   = highlighted ? 0.095f : 0.082f;
    int   segments = 32;
    float r = node.colorR, g = node.colorG, b = node.colorB;

    // Тень
    glColor4f(0, 0, 0, 0.35f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(nx + 0.012f, ny - 0.012f);
    for (int i = 0; i <= segments; ++i) {
        float a = 2.0f * M_PI * i / segments;
        glVertex2f(nx + 0.012f + cosf(a)*radius, ny - 0.012f + sinf(a)*radius);
    }
    glEnd();

    // Тело
    float bright = highlighted ? 1.0f : 0.7f;
    glColor4f(r*bright, g*bright, b*bright, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(nx, ny);
    for (int i = 0; i <= segments; ++i) {
        float a = 2.0f * M_PI * i / segments;
        glVertex2f(nx + cosf(a)*radius, ny + sinf(a)*radius);
    }
    glEnd();

    // Обводка
    glColor4f(1, 1, 1, highlighted ? 1.0f : 0.4f);
    glLineWidth(highlighted ? 2.0f : 1.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        float a = 2.0f * M_PI * i / segments;
        glVertex2f(nx + cosf(a)*radius, ny + sinf(a)*radius);
    }
    glEnd();
}

void GraphWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (m_nodes.isEmpty()) {
        QPainter p(this);
        p.setPen(QColor(120, 120, 150));
        p.setFont(QFont("Arial", 11));
        p.drawText(rect(), Qt::AlignCenter,
                   "Нажмите «🔗 Найти цепочки»\nдля отображения графа обменов");
        p.end();
        return;
    }

    // Интерполяция позиций
    QVector<float> curX(m_nodes.size()), curY(m_nodes.size());
    for (int i = 0; i < m_nodes.size(); ++i) {
        curX[i] = m_nodes[i].x + (m_nodes[i].targetX - m_nodes[i].x) * m_animProgress;
        curY[i] = m_nodes[i].y + (m_nodes[i].targetY - m_nodes[i].y) * m_animProgress;
    }

    // Рёбра
    for (const GraphEdge &e : m_edges) {
        int fi = m_nodeIndex.value(e.fromItemId, -1);
        int ti = m_nodeIndex.value(e.toItemId,   -1);
        if (fi < 0 || ti < 0) continue;

        bool  hl    = e.highlighted || m_highlightedChain < 0;
        float alpha = hl ? 0.95f : 0.15f;

        drawArrow(curX[fi], curY[fi], curX[ti], curY[ti],
                  m_nodes[fi].colorR, m_nodes[fi].colorG, m_nodes[fi].colorB, alpha);
    }

    // Узлы
    for (int i = 0; i < m_nodes.size(); ++i) {
        bool isInChain = (m_highlightedChain < 0);
        if (!isInChain && m_highlightedChain < m_chains.size())
            for (const ChainStep &s : m_chains[m_highlightedChain].steps)
                if (s.giverId == m_nodes[i].itemId) { isInChain = true; break; }
        GraphNode tmp = m_nodes[i];
        tmp.x = curX[i]; tmp.y = curY[i];
        drawNode(tmp, isInChain);
    }

    // Подписи
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    float aspect = (height() > 0) ? float(width()) / height() : 1.0f;

    auto glToScreen = [&](float gx, float gy) -> QPointF {
        return QPointF(
            (gx + aspect) / (2.0f * aspect) * width(),
            (1.0f - (gy + 1.0f) / 2.0f) * height()
        );
    };

    for (int i = 0; i < m_nodes.size(); ++i) {
        bool isInChain = (m_highlightedChain < 0);
        if (!isInChain && m_highlightedChain < m_chains.size())
            for (const ChainStep &s : m_chains[m_highlightedChain].steps)
                if (s.giverId == m_nodes[i].itemId) { isInChain = true; break; }

        QPointF pos = glToScreen(curX[i], curY[i]);
        int alpha   = isInChain ? 255 : 70;

        painter.setFont(QFont("Arial", 8, QFont::Bold));
        painter.setPen(QColor(255, 255, 255, alpha));
        painter.drawText(QRectF(pos.x()-52, pos.y()-10, 104, 14),
                         Qt::AlignCenter, m_nodes[i].ownerName);

        painter.setFont(QFont("Arial", 7));
        painter.setPen(QColor(180, 220, 255, alpha));
        QString sn = m_nodes[i].itemName.length() > 13
                     ? m_nodes[i].itemName.left(12) + "…"
                     : m_nodes[i].itemName;
        painter.drawText(QRectF(pos.x()-52, pos.y()+3, 104, 12),
                         Qt::AlignCenter, sn);
    }

    // Легенда
    if (m_chains.size() > 1) {
        float cc[][3] = {
            {0.2f,0.6f,1.0f},{0.3f,0.85f,0.4f},{1.0f,0.5f,0.1f},
            {0.9f,0.2f,0.4f},{0.7f,0.3f,1.0f}
        };
        painter.setFont(QFont("Arial", 8));
        for (int i = 0; i < qMin(m_chains.size(), 5); ++i) {
            painter.fillRect(QRectF(8, 8+i*18, 12, 12),
                QColor(cc[i%5][0]*255, cc[i%5][1]*255, cc[i%5][2]*255));
            painter.setPen(Qt::white);
            painter.drawText(QRectF(24, 8+i*18, 140, 14), Qt::AlignVCenter,
                QString("Цепочка %1 (%2 шага)").arg(i+1).arg(m_chains[i].length()));
        }
    }

    painter.setFont(QFont("Arial", 7));
    painter.setPen(QColor(100, 100, 130));
    painter.drawText(QRectF(0, height()-16, width(), 14),
                     Qt::AlignCenter,
                     "Стрелка → показывает кто кому отдаёт предмет");
    painter.end();
}
