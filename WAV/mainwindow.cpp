#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{ 
    player = new QMediaPlayer;
    ui->setupUi(this);
    this->speed = double(ui->horizontalSlider->value()) / 100.0;
    ui->label_speed->setNum(speed);
    ui->playButton->setEnabled(false);
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setSpeed(int)));
    connect(this, SIGNAL(speedChanged(double)), ui->label_speed, SLOT(setNum(double)));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(showAboutInfo()));
    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(playSound()));
}

MainWindow::~MainWindow()
{
    delete player;
    delete ui;
}

void MainWindow::setSpeed(int val) {
    this->speed = val / 100.0;
    emit speedChanged(speed);
}

void MainWindow::openFile() {
    this->filename =  QFileDialog::getOpenFileName(
              this,
              "Choose audiofile",
              QDir::currentPath(),
              "WAV files (*.wav)"
    );
    ui->label_file->setText(filename);
    ui->playButton->setEnabled(true);
}

void MainWindow::saveFile() {
    qDebug() << "save";
}

void MainWindow::showAboutInfo() {
    QMessageBox::information(this, "About", "Copyright (c) 2018 Anton Myronyuk");
}

void MainWindow::playSound() {
    qDebug() << "play";

    player->setMedia(QUrl::fromLocalFile(filename));
    player->setVolume(100);
    player->play();


}
