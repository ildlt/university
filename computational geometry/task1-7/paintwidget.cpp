#include "paintwidget.h"
#include "ui_paintwidget.h"
#include "Predicates.h"
#include <QMouseEvent>
#include <QPoint>
#include <QPainter>

PaintWidget::PaintWidget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::PaintWidget),
    cursorPoint(nullptr),
    pointSelection(false) {
    ui->setupUi(this);
    setMouseTracking(true);
    exact::Init();
}

void PaintWidget::mousePressEvent(QMouseEvent *event) {
    QPoint* currentPoint = new QPoint(event->x(), event->y());
    cursorPoint = new QPoint(event->x(), event->y());

    if (pointSelection) {
        QPoint* firstPoint = &points.first();
        if (pointsAreClose(firstPoint, currentPoint)) {
            pointSelection = false;
        } else {
            points.push_back(*currentPoint);
        }
    } else {
        points.clear();
        pointSelection = true;
        points.push_back(*currentPoint);
    }

    update();
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event) {
    delete cursorPoint;
    cursorPoint = new QPoint(event->x(), event->y());

    update();
}

bool PaintWidget::pointsAreClose(QPoint *point1, QPoint *point2) {
    int dx = point1->x() - point2->x();
    int dy = point1->y() - point2->y();

    return dx * dx + dy * dy < 300;
}

void PaintWidget::paintEvent(QPaintEvent *event) {
    if (points.size() > 0) {
        QPainter painter(this);

        QPen pen;
        pen.setColor(Qt::black);
        pen.setWidth(5);
        painter.setPen(pen);

        for (int i = 0; i < points.size(); i++) {
            painter.drawPoint(points[i]);
        }

        pen.setColor(Qt::green);
        pen.setWidth(2);
        painter.setPen(pen);

        for (int i = 1; i < points.size(); i++) {
            painter.drawLine(points[i - 1], points[i]);
        }

        if (pointSelection) {
            painter.drawLine(points.last(), *cursorPoint);

            if (pointsAreClose(&points.first(), cursorPoint)) {
                pen.setColor(Qt::black);
                pen.setWidth(12);
                painter.setPen(pen);
                painter.drawPoint(points.first());
            }
        } else {
            painter.drawLine(points.last(), points.first());

            if (isCursorInsidePolygon()) {
                QBrush brush;
                brush.setColor(Qt::darkGreen);
                brush.setStyle(Qt::DiagCrossPattern);
                painter.setBrush(brush);
                painter.drawPolygon(points.data(), points.size());
            }
        }
    }
}

bool PaintWidget::isCursorInsidePolygon() {
    if (points.size() == 1) {
        return theSame(cursorPoint, &points[0]);
    }

    int maxX = -1;
    for (int i = 0; i < points.size(); i++) {
        if (points[i].x() > maxX) {
            maxX = points[i].x();
        }
    }

    QPoint* pa = cursorPoint;
    QPoint* pb = new QPoint(maxX + 10, cursorPoint->y());

    int j = 0;
    QPoint* p = &points[j];
    while (isPointOnSegment(pa, pb, p)) {
        p = &points[++j];
    }

    int ctr = 0;
    int i = 0;
    while (i < points.size()) {
        QPoint* pc = &points[(j + i) % points.size()];
        QPoint* pd = &points[(j + i + 1) % points.size()];

        if (isPointOnSegment(pc, pd, pa)) {
            return true;
        }

        if (segmentsIntersect(pa, pb, pc, pd)) {
            ctr++;
        }

        if (isPointOnSegment(pa, pb, pd)) {
            QPoint* p = pd;
            while (isPointOnSegment(pa, pb, p)) {
                i++;
                p = &points[(j + i + 1) % points.size()];
            }

            if (exact::orient2d(coords(pa), coords(pb), coords(pc)) !=
                exact::orient2d(coords(pa), coords(pb), coords(p))) {
                ctr++;
            }
        }

        i++;
    }

    return ctr % 2 != 0;
}

bool PaintWidget::segmentsIntersect(QPoint *pa, QPoint *pb, QPoint *pc, QPoint *pd) {
    int orientA = exact::orient2d(coords(pc), coords(pd), coords(pa));
    int orientB = exact::orient2d(coords(pc), coords(pd), coords(pb));
    bool onTheSameSide1 = orientA == orientB;

    int orientC = exact::orient2d(coords(pa), coords(pb), coords(pc));
    int orientD = exact::orient2d(coords(pa), coords(pb), coords(pd));
    bool onTheSameSide2 = orientC == orientD;

    bool onSegment = isPointOnSegment(pa, pb, pc) ||
                    isPointOnSegment(pa, pb, pd) ||
                    isPointOnSegment(pc, pd, pa) ||
                    isPointOnSegment(pc, pd, pb);

    if (!onSegment && !onTheSameSide1 && !onTheSameSide2) {
        return true;
    }

    return false;
}

bool PaintWidget::isPointOnSegment(QPoint *pa, QPoint *pb, QPoint *pc) {
    if (theSame(pa, pc) || theSame(pb, pc)) {
        return true;
    }

    bool isPointOnLine = !exact::orient2d(coords(pa), coords(pb), coords(pc));
    bool isBetweenPointsX = (pa->x() < pc->x() && pb->x() > pc->x()) ||
                            (pa->x() > pc->x() && pb->x() < pc->x());

    return isPointOnLine && isBetweenPointsX;
}

bool PaintWidget::theSame(QPoint *pa, QPoint *pb) {
    return (pa->x() == pb->x()) && (pa->y() == pb->y());
}

double* PaintWidget::coords(QPoint* point) {
    double *cds = new double[2];
    cds[0] = point->x();
    cds[1] = point->y();
    return cds;
}

PaintWidget::~PaintWidget()
{
    delete ui;
}
