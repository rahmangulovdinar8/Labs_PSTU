#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMap>
#include <QTimer>
#include "item.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = nullptr);
    void setData(const QMap<ItemCategory, int> &counts, int totalItems);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    void drawBar(float x, float y, float w, float h,
                 float r, float g, float b);
    void drawGrid();

    QMap<ItemCategory, int> m_counts;
    int     m_total;
    float   m_animProgress;
    QTimer *m_animTimer;
};

#endif // GLWIDGET_H
