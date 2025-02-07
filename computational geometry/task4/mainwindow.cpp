#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    width = ui->widget->width();
    height = ui->widget->height();
    pointDiameter = 3;
    pixmap = QPixmap(width, height);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_goButton_clicked() {
    points.clear();
    repaint();
}

double MainWindow::getCoordinate(double t, bool get_x = true) {
    std::vector<std::vector<double>> b;
    int n = points.size() - 1;

    for (int i = 0; i < n + 1; ++i) {
        b.push_back(std::vector<double>(n + 1, 0));
    }

    for (int i = 0; i < n + 1; ++i) {
        if (get_x)
            b[0][i] = points[i].x();
        else
            b[0][i] = points[i].y();
    }

    for (int r = 1; r < n + 1; ++r) {
        for (int i = 0; i < n - r + 1; ++i) {
            b[r][i] = (1 - t) * b[r - 1][i] + t * b[r - 1][i + 1];
        }
    }

    return b[n][0];
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QBrush brush(Qt::green);
    painter.setBrush(brush);

    pixmap.fill(Qt::white);
    painter.drawPixmap(0, 0, pixmap);

    for(auto point: points) {
        painter.drawEllipse(point, pointDiameter, pointDiameter);
    }

    if(points.size() <= 2)
        return;

    brush.setColor(Qt::black);
    painter.setBrush(brush);

    QPen pen(Qt::darkGreen);
    pen.setWidth(3);
    painter.setPen(pen);

    for (int i=0; i<=2500; ++i) {
        double t = i/2500.0;
        QPoint point = QPoint(static_cast<int>(getCoordinate(t, true)), static_cast<int>(getCoordinate(t, false)));
        if (i == 0 || i == 2500) {
            pen.setWidth(1);
            painter.setPen(pen);
            painter.drawEllipse(point, pointDiameter, pointDiameter);
        } else {
            painter.drawPoint(point);
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        return;
    }
    for (int i=0; i<static_cast<int>(points.size()); ++i) {
        if(std::abs(event->x() - points[i].x()) <= pointDiameter/2 && std::abs(event->y() - points[i].y()) <= pointDiameter/2) {
            movingPoint = i;
            isMovingLine = true;
        }
    }
    if(!isMovingLine) {
        points.emplace_back(event->x(), event->y());
    }
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    isMovingLine = false;
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if(isMovingLine) {
        points[movingPoint] = QPoint(event->x(), event->y());
    }
    update();
}
