#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTextStream>
#include <QMouseEvent>
#include <ctime>
#include <iostream>
#include <vector>
#include <QGenericMatrix>
#include <QTextEdit>
#include <math.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef QGenericMatrix<1, 3, float> QMatrix1x3;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void redrawPixmap();
    void update_edges(QMatrix3x3);
    void paintEvent(QPaintEvent *);
    void createProjection(QPainter &tempPainter);
    void createSquare(double a);

private slots:
    void on_textEditX_textChanged();
    void on_textEditY_textChanged();
    void on_textEditZ_textChanged();

private:
    Ui::MainWindow *ui;
    std::vector<std::pair<QMatrix1x3, QMatrix1x3>> edges;
    QPainter painter;
    QPixmap pixmap;
    int HEIGHT = 100;
    const double angle = M_PI/4;
    int prevx = 0, prevy = 0, prevz = 0;
};
#endif // MAINWINDOW_H
