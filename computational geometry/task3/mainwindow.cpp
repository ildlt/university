#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->addWidget(&wdg);
    ui->stackedWidget->setCurrentWidget(&wdg);
    this->adjustSize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    wdg.addPoints();
}

void MainWindow::on_clearButton_clicked()
{
    wdg.clearImage();
}

void MainWindow::on_runButton_clicked()
{
    wdg.runHull();
}
