#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{ 
    ui->setupUi(this);
    this->speed = double(ui->horizontalSlider->value()) / 100.0;
    ui->label_speed->setNum(speed);
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setSpeed(int)));
    connect(this, SIGNAL(speedChanged(double)), ui->label_speed, SLOT(setNum(double)));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(showAboutInfo()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSpeed(int val) {
    this->speed = val / 100.0;
    emit speedChanged(speed);
}

void MainWindow::openFile() {
    std::cout << "open" << std::endl;
}

void MainWindow::saveFile() {
    std::cout << "save" << std::endl;
}

void MainWindow::showAboutInfo() {
    QMessageBox::information(this, "About", "Copyright © 2018 - Anton Myronyuk");
}
