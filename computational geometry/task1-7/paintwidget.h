#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QVector>

namespace Ui {
    class PaintWidget;
}

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PaintWidget(QWidget *parent = nullptr);
    ~PaintWidget();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Ui::PaintWidget *ui;

    QVector<QPoint> points;
    QPoint* cursorPoint;
    bool pointSelection;

    bool pointsAreClose(QPoint* point1, QPoint* point2);
    bool isCursorInsidePolygon();
    bool segmentsIntersect(QPoint* pa, QPoint* pb, QPoint* pc, QPoint* pd);
    bool isPointOnSegment(QPoint* pa, QPoint* pb, QPoint* pc);
    bool theSame(QPoint* pa, QPoint* pb);
    double* coords(QPoint* point);

signals:
    void emitPoints(QPoint* points);
};

#endif // PAINTWIDGET_H
