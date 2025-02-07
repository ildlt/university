#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRgb>

// getting the coordinates
float get_x(QMatrix1x3 t) {
    return t.data()[0];
}

float get_y(QMatrix1x3 t) {
    return t.data()[1];
}

float get_z(QMatrix1x3 t) {
    return t.data()[2];
}

// conversion
double convert_to_radian(double action) {
    return action / 360 * 2 * M_PI;
}

QMatrix1x3 make_point(float x, float y, float z) {
    float data[] = {x, y, z};
    return QMatrix1x3(data);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pixmap = QPixmap(this->width(), this->height() - HEIGHT);
    pixmap.fill(Qt::white);

    createSquare(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createSquare(double a)
{
    QMatrix1x3 p1 = make_point(-a, a, a);
    QMatrix1x3 p2 = make_point(-a, a, -a);
    QMatrix1x3 p3 = make_point(a, a, a);
    QMatrix1x3 p4 = make_point(a, a, -a);
    QMatrix1x3 p5 = make_point(-a, -a, a);
    QMatrix1x3 p6 = make_point(-a, -a, -a);
    QMatrix1x3 p7 = make_point(a, -a, a);
    QMatrix1x3 p8 = make_point(a, -a, -a);

    edges = {
         std::make_pair(p1, p2),
         std::make_pair(p1, p3),
         std::make_pair(p1, p5),
         std::make_pair(p2, p4),
         std::make_pair(p2, p6),
         std::make_pair(p4, p3),
         std::make_pair(p4, p8),
         std::make_pair(p3, p7),
         std::make_pair(p5, p6),
         std::make_pair(p6, p8),
         std::make_pair(p7, p8),
         std::make_pair(p5, p7)
    };
}

void MainWindow::update_edges(QMatrix3x3 rotate_m) {
    for (size_t i = 0; i < edges.size(); i++) {
        edges[i] = std::make_pair(rotate_m * edges[i].first, rotate_m * edges[i].second);
    }

    pixmap.fill(Qt::white);
    update();
}

QMatrix3x3 x_matrix(double action) {
    double theta = convert_to_radian(action);
    float data[] = {1, 0, 0,
                    0, (float) cos(theta), (float) sin(theta),
                    0, (float) -sin(theta), (float) cos(theta)};
    return QMatrix3x3(data);
}

QMatrix3x3 y_matrix(double action) {
    double theta = convert_to_radian(action);
    float data[] = {(float) cos(theta), 0, (float) -sin(theta),
                    0, 1, 0,
                    (float) sin(theta), 0, (float) cos(theta)};
    return QMatrix3x3(data);
}

QMatrix3x3 z_matrix(double action) {
    double theta = convert_to_radian(action);
    float data[] = {(float) cos(theta), (float) sin(theta), 0,
                    (float) -sin(theta), (float) cos(theta), 0,
                    0, 0, 1};
    return QMatrix3x3(data);
}

QMatrix3x3 rotate_matrix(double x, double y, double z) {
    return x_matrix(x) * y_matrix(y) * z_matrix(z);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter tempPainter(&pixmap);

    createProjection(tempPainter);

    painter.begin(this);
    painter.drawPixmap(150, 0, pixmap);
    painter.end();
}

void MainWindow::createProjection(QPainter &tempPainter)
{
    int centerX = this->width() / 2, centerY = (this->height() - HEIGHT) / 2;

    for (size_t i = 0; i < edges.size(); i++) {
        float x1 = get_x(edges[i].first), y1 = get_y(edges[i].first), z1 = get_z(edges[i].first);
        float x2 = get_x(edges[i].second), y2 = get_y(edges[i].second), z2 = get_z(edges[i].second);

        QPoint p1(x1 + centerX + z1 * cos(angle), y1 + centerY + z1 * sin(angle));
        QPoint p2(x2 + centerX + z2 * cos(angle), y2 + centerY + z2 * sin(angle));
        QPen penHLines(QColor(i*20, 60, 60), 2);
        tempPainter.setPen(penHLines);
        tempPainter.drawLine(p1, p2);
    }
}

void MainWindow::on_textEditX_textChanged()
{
    const QString text = ui->textEditX->toPlainText();
    bool is_parsed = true;
    int curx = text.toInt(&is_parsed);
    if (!is_parsed) return;
    update_edges(rotate_matrix(curx - prevx, 0, 0));
    prevx = curx;
}

void MainWindow::on_textEditY_textChanged()
{
    const QString text = ui->textEditY->toPlainText();
    bool is_parsed = true;
    int cury = text.toInt(&is_parsed);
    if (!is_parsed) return;
    update_edges(rotate_matrix(0, cury - prevy, 0));
    prevy = cury;
}

void MainWindow::on_textEditZ_textChanged()
{
    const QString text = ui->textEditZ->toPlainText();
    bool is_parsed = true;
    int curz = text.toInt(&is_parsed);
    if (!is_parsed) return;
    update_edges(rotate_matrix(0, 0, curz - prevz));
    prevz = curz;
}
