#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QStackedWidget>
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QList>
#include <QPoint>
#include <vector>

class mainwidget : public QWidget
{
public:
    mainwidget();
    void clearImage();
    void addPoints();
    void runHull();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::vector<QPoint> points;
    std::vector<QPoint> hull;
    QImage image;
    int N;
    int M;
    bool is_running, is_finished;
};

#endif // MAINWIDGET_H
