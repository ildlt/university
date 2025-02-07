#include "mainwidget.h"
#include <iostream>
#include <queue>
#include <vector>
#include <chrono>
#include <thread>
#include <time.h>

#include <QtWidgets>

#define F first
#define S second

mainwidget::mainwidget()
{
    srand(time(0));
    N = 1000;
    M = 600;
    QImage newImage(QSize(N, M), QImage::Format_RGB32);
    newImage.fill(Qt::white);
    this->setFixedSize(N, M);

    // Draw the image
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), image);
    image = newImage;
    is_finished = false;
}

struct pt {
    int x, y;
};

double getAngle(QPoint a, QPoint b)
{
    return  (static_cast<double>(a.y() - b.y()) / static_cast<double>(b.x() - a.x()));
}

void delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(50);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void mainwidget::addPoints()
{
    QPainter painter(&image);
    painter.setPen(QPen(Qt::red, 6));
    for (int i = 0; i < 1000; i++)
    {
        int x = rand() % (N - 100) + 50;
        int y = rand() % (M - 100) + 50;
        points.push_back(QPoint(x, y));
        painter.drawPoint(x, y);
    }
    update();
}

int isLeftTurn(const QPoint &p0, const QPoint &p1, const QPoint &p2){
    return (p1.x() - p0.x())*(p1.y() - p2.y()) - (p2.x() - p1.x())*(p0.y() - p1.y());
}

void mainwidget::runHull()
{
    is_running = true;
    QPoint firstPoint(N, M);

    if(points.size() < 2)
        return;

    for (auto point : points)
    {
        if (point.x() < firstPoint.x()){
            firstPoint = point;
        }
    }
    auto comp = [&](const QPoint &a,const QPoint &b) -> bool {

        if (a == firstPoint)
            return true;
        if (b == firstPoint)
            return false;
        return getAngle(firstPoint, a) < getAngle(firstPoint, b);
    };

    sort(points.begin(), points.end(), comp);

    hull.push_back(points[0]);
    hull.push_back(points[1]);
    hull.push_back(points[2]);

    update();
    for (int i = 3; i < static_cast<int>(points.size()); i++)
    {
        QPoint v = hull.back();
        hull.pop_back();
        QPoint w = points[i];
        while (hull.size() && isLeftTurn(hull.back(), v, w) <= 0)
        {
            v = hull.back();
            hull.pop_back();
        }
        hull.push_back(v);
        hull.push_back(w);
     }
    is_finished = true;
    update();

}

// Color the image area with white
void mainwidget::clearImage()
{
    image.fill(Qt::white);
    points.clear();
    hull.clear();
    is_running = false;
    is_finished = false;
    update();
}

void mainwidget::paintEvent(QPaintEvent *event)
{

    QImage new_im = image;
    QPainter painter_m(&new_im);


    if (is_running)
    {
        for (int i = 1; i < hull.size(); i++)
        {
            painter_m.setPen(QPen(Qt::green, 2, Qt::SolidLine));
            painter_m.drawLine( hull[i-1], hull[i]);
        }
    }

    if (is_finished)
    {
        painter_m.drawLine(hull[0], hull.back());
    }


    QPainter painter(this);

    // Returns the rectangle that needs to be updated
    QRect dirtyRect = event->rect();

//    // Draws the rectangle where the image needs to
//    // be updated
    painter.drawImage(dirtyRect, new_im, dirtyRect);
}
