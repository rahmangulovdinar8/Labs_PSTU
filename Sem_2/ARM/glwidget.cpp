#include "glwidget.h"
#include <QPainter>
#include <QtMath>
#include <GL/gl.h>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent), m_total(0), m_animProgress(0.0f)
{
    m_animTimer = new QTimer(this);
    connect(m_animTimer, &QTimer::timeout, this, [this](){
        m_animProgress += 0.04f;
        if (m_animProgress >= 1.0f) {
            m_animProgress = 1.0f;
            m_animTimer->stop();
        }
        update();
    });
}

void GLWidget::setData(const QMap<ItemCategory, int> &counts, int totalItems) {
    m_counts = counts;
    m_total  = totalItems;
    m_animProgress = 0.0f;
    m_animTimer->start(16);
}

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.12f, 0.12f, 0.18f, 1.0f);
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::drawBar(float x, float y, float w, float h,
                        float r, float g, float b)
{
    // Тело столбца
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x,   y);
        glVertex2f(x+w, y);
        glVertex2f(x+w, y+h);
        glVertex2f(x,   y+h);
    glEnd();

    // Светлая верхняя грань (3D-эффект)
    glColor3f(qMin(r+0.3f,1.0f), qMin(g+0.3f,1.0f), qMin(b+0.3f,1.0f));
    glBegin(GL_QUADS);
        glVertex2f(x,     y+h);
        glVertex2f(x+w,   y+h);
        glVertex2f(x+w,   y+h+0.12f);
        glVertex2f(x,     y+h+0.12f);
    glEnd();

    // Тёмная правая грань
    glColor3f(r*0.5f, g*0.5f, b*0.5f);
    glBegin(GL_QUADS);
        glVertex2f(x+w,       y);
        glVertex2f(x+w+0.12f, y+0.06f);
        glVertex2f(x+w+0.12f, y+h+0.06f);
        glVertex2f(x+w,       y+h);
    glEnd();

    // Контур
    glColor3f(1,1,1);
    glLineWidth(1.2f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x,   y);
        glVertex2f(x+w, y);
        glVertex2f(x+w, y+h);
        glVertex2f(x,   y+h);
    glEnd();
}

void GLWidget::drawGrid() {
    glColor3f(0.25f, 0.25f, 0.35f);
    glLineWidth(1.0f);
    // Горизонтальные линии сетки
    for (int i = 1; i <= 5; ++i) {
        float y = 1.0f + i * 1.2f;
        glBegin(GL_LINES);
            glVertex2f(0.5f, y);
            glVertex2f(9.5f, y);
        glEnd();
    }
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawGrid();

    struct CatInfo { ItemCategory cat; float r,g,b; const char* label; };
    CatInfo cats[] = {
        { ItemCategory::Electronics, 0.2f, 0.6f, 1.0f, "Электр."  },
        { ItemCategory::Books,       0.3f, 0.8f, 0.3f, "Книги"    },
        { ItemCategory::Clothing,    1.0f, 0.5f, 0.2f, "Одежда"   },
        { ItemCategory::Food,        1.0f, 0.8f, 0.1f, "Еда"      },
        { ItemCategory::Hygiene,     0.2f, 0.9f, 0.8f, "Гигиена"  },
        { ItemCategory::SportGame,   0.9f, 0.3f, 0.5f, "Спорт"    },
        { ItemCategory::Stationery,  0.8f, 0.7f, 0.1f, "Канцел."  },
        { ItemCategory::Furniture,   0.6f, 0.4f, 0.2f, "Быт"      },
        { ItemCategory::Other,       0.7f, 0.7f, 0.7f, "Прочее"   },
    };
    int numCats = 9;

    int maxVal = 1;
    for (auto &c : cats) {
        int v = m_counts.value(c.cat, 0);
        if (v > maxVal) maxVal = v;
    }

    float barW   = 0.72f;
    float gapX   = 0.28f;
    float startX = 0.4f;
    float baseY  = 1.0f;
    float maxH   = 6.5f;

    for (int i = 0; i < numCats; ++i) {
        int val = m_counts.value(cats[i].cat, 0);
        float targetH = (maxVal > 0) ? (float(val) / maxVal) * maxH : 0.0f;
        float h = targetH * m_animProgress; // анимация

        float x = startX + i * (barW + gapX);
        if (h > 0.0f)
            drawBar(x, baseY, barW, h, cats[i].r, cats[i].g, cats[i].b);
    }


    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Заголовок
    painter.setPen(Qt::white);
    QFont titleFont("Arial", 10, QFont::Bold);
    painter.setFont(titleFont);
    painter.drawText(rect(), Qt::AlignTop | Qt::AlignHCenter,
                     QString("Предметов по категориям  (всего: %1)").arg(m_total));

    QFont labelFont("Arial", 7);
    painter.setFont(labelFont);
    int widgetW = width();
    int widgetH = height();


    for (int i = 0; i < numCats; ++i) {
        int val = m_counts.value(cats[i].cat, 0);

        // Центр столбца в GL-координатах (те же что в drawBar)
        float barCenterGL = startX + i * (barW + gapX) + barW * 0.5f;
        float pixelX = (barCenterGL / 10.0f) * widgetW;

        // Подпись под столбцом (у основания)
        float labelY = widgetH - (baseY / 10.0f) * widgetH + 2;
        painter.setPen(QColor(200, 200, 200));
        painter.drawText(QRectF(pixelX - 34, labelY, 68, 14),
                         Qt::AlignCenter, QString(cats[i].label));

        // Цифра над столбцом
        if (val > 0) {
            float targetH  = (float(val) / maxVal) * maxH;
            float barTopGL = baseY + targetH * m_animProgress;
            float numPixY  = widgetH - (barTopGL / 10.0f) * widgetH - 16;
            painter.setPen(Qt::white);
            painter.setFont(QFont("Arial", 8, QFont::Bold));
            painter.drawText(QRectF(pixelX - 18, numPixY, 36, 14),
                             Qt::AlignCenter, QString::number(val));
            painter.setFont(labelFont);
        }
    }
    painter.end();
}
