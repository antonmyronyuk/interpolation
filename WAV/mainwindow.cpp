#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{ 
    srand(time(0));
    this->tmpFilename = "temp.wav";
    ui->setupUi(this);
    player = new QSoundEffect;
    this->speed = double(ui->horizontalSlider->value()) / 100.0;
    ui->label_speed->setNum(speed);
    ui->playButton->setEnabled(false);
    ui->stopButton->setEnabled(false);
    ui->resizeButton->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);
    ui->actionSave->setEnabled(false);

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setSpeed(int)));
    connect(this, SIGNAL(speedChanged(double)), ui->label_speed, SLOT(setNum(double)));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(showAboutInfo()));
    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(playSound()));
    connect(ui->stopButton, SIGNAL(clicked(bool)), this, SLOT(stopSound()));
    connect(ui->resizeButton, SIGNAL(clicked(bool)), this, SLOT(resizeSound()));
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
    this->filename =  QFileDialog::getOpenFileName(
              this,
              "Choose audiofile",
              QDir::currentPath(),
              "WAV files (*.wav)"
    );
    ui->label_file->setText(filename);
    ui->playButton->setEnabled(true);
    ui->stopButton->setEnabled(true);
    ui->resizeButton->setEnabled(true);
    ui->horizontalSlider->setEnabled(true);
    ui->actionSave->setEnabled(true);
    this->input.readFromFile(filename);
    this->output = this->input;
    this->output.saveToFile(this->tmpFilename);

}

void MainWindow::saveFile() {
    qDebug() << "save";
    QFile tmp(this->tmpFilename);
    tmp.remove();
}

void MainWindow::showAboutInfo() {
    QMessageBox::information(this, "About", "Copyright (c) 2018 Anton Myronyuk");
}

void MainWindow::playSound() {

    qDebug() << "play";
    /*
    if (player) {
        player->~QSound();
    }
    player = NULL;
    player = new QSound(this->tmpFilename);

    player->play();
    */
    player->setSource(QUrl::fromLocalFile(this->tmpFilename));
    player->play();

}

void MainWindow::stopSound() {
    /*
    qDebug() << "stop";
    if (player) {
        player->~QSound();
        player = NULL;
    }
    */
    player->stop();
}

void MainWindow::resizeSound() {
    qDebug() << "resize";
    //TODO: use normal temporary file in future
    WavFile::resize(input, output, 1.0 / speed);
    this->output.saveToFile(this->tmpFilename);
    //this->output.saveToFile("1.wav");
    QMessageBox::information(this, "Resize", "Done! Now you can play this and save it.");

}
