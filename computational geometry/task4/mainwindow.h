#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>
#include <QPen>
#include <algorithm>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    double getCoordinate(double t, bool get_x);

private slots:
    void on_goButton_clicked();

private:
    Ui::MainWindow *ui;
    int width;
    int height;
    int pointDiameter;
    int movingPoint = -1;
    bool isMovingLine= false;
    QPixmap pixmap;
    std::vector<QPoint> points;
};
#endif // MAINWINDOW_H
