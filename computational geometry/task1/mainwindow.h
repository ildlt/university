#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTextStream>
#include <QMouseEvent>
#include <vector>
#include <set>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int COUNT;
    int WIDTH = 150;
    int MAX_LEN = 20;
    bool segmentsGenerated, segmentsDrawn, segmentsIntersected, segmentsIntersectedDrawn;

protected:
    void redrawPixmap();
    void paintEvent(QPaintEvent *);
    std::vector<QLine> generateSegments(int maxX, int maxY, int maxLen);
    std::multimap<int, int> coordSet;

private slots:
    void on_buttonDraw_clicked();
    void on_buttonSolve_clicked();
    void on_buttonClear_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<QLine> segments;
    QPainter painter;
    QPixmap mPix;
};
#endif // MAINWINDOW_H
