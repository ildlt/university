#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mPix = QPixmap(this->width() - WIDTH, this->height());
    mPix.fill(Qt::white);
    segmentsGenerated = false;
    segmentsIntersected = false;
    segmentsDrawn = false;
    segmentsIntersectedDrawn = false;
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter tempPainter(&mPix);

    if (segmentsGenerated && !segmentsDrawn) {
        for (size_t i = 0; i < segments.size(); i++) {
            tempPainter.drawLine(segments[i]);
        }
        segmentsDrawn = true;
    }

    if (segmentsGenerated && segmentsIntersected && !segmentsIntersectedDrawn) {
        tempPainter.setPen(QPen(Qt::green));
        std::set<int> segments_to_draw;
        QLine cur_segment;
        std::multimap<int, int> mapping;

        for (auto curXSegmentIndexPair: coordSet) {
            cur_segment = segments[curXSegmentIndexPair.second];
            if (cur_segment.x1() == cur_segment.x2()) {
                bool isIntersected = false;
                for (auto horizSegmentIndexYPair: mapping) {
                    if (horizSegmentIndexYPair.second >= cur_segment.y1() && cur_segment.y2() >= horizSegmentIndexYPair.second){
                        segments_to_draw.insert(horizSegmentIndexYPair.first);
                        isIntersected = true;
                    }
                }
                if (isIntersected) segments_to_draw.insert(curXSegmentIndexPair.second);
            }
            else if (curXSegmentIndexPair.first == cur_segment.x1())
                mapping.emplace(curXSegmentIndexPair.second, cur_segment.y1());
            else
                mapping.erase(curXSegmentIndexPair.second);
        }

        for (auto segment_index: segments_to_draw) {
            tempPainter.drawLine(segments[segment_index]);
        }

        segmentsIntersectedDrawn = true;
    }

    redrawPixmap();
}

std::vector<QLine> MainWindow::generateSegments(int maxX, int maxY, int maxLen) {
    coordSet.clear();
    int x1, y1, x2, y2, len;

    std::vector<QLine> newSegments;
    srand(time(NULL));
    std::multimap<int, int> endsOfHorizontalSegments;

    for (int i = 0; i < COUNT; i++) {
        x1 = (rand() % maxX);
        y1 = (rand() % maxY);
        len = (rand() % maxLen);

        if (rand() % 2) {
            x2 = x1;
            while (y1 + len > maxY) {
                len = (rand() % maxLen);
            }
            y2 = y1+len;
        }
        else {
            y2 = y1;
            while (x1+len > maxX) {
                len = (rand() % maxLen);
            }
            x2 = x1+len;
            endsOfHorizontalSegments.emplace(x2, i);
        }

        coordSet.emplace(x1, i);

        newSegments.push_back(QLine(QPoint(x1, y1), QPoint(x2, y2)));
    }

    for (auto endOfHor: endsOfHorizontalSegments) {
        coordSet.insert(endOfHor);
    }

    return newSegments;
}

void MainWindow::redrawPixmap() {
    painter.begin(this);
    painter.drawPixmap(150, 0, mPix);
    painter.end();
}

void MainWindow::on_buttonDraw_clicked() {
    segmentsGenerated = false;
    mPix.fill(Qt::white);

    const QString text = ui->segmentsCount->text();
    bool is_parsed = true;
    COUNT = text.toInt(&is_parsed);
    if (!is_parsed) return;

    segments = generateSegments(this->width() - WIDTH, this->height(), MAX_LEN);
    segmentsGenerated = true;
    segmentsIntersected = false;
    segmentsDrawn = false;
    segmentsIntersectedDrawn = false;

    update();
}

void MainWindow::on_buttonSolve_clicked() {
    segmentsIntersected = true;
    update();
}

void MainWindow::on_buttonClear_clicked()
{
    segmentsGenerated = false;
    mPix.fill(Qt::white);
    update();
}
