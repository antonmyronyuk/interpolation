#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QUrl>
#include <QFile>
#include "wavfile.h"
#include <time.h>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    double speed;
    QString filename;
    QString tmpFilename;
    WavFile input;
    WavFile output;

signals:
    void speedChanged(double);
private slots:
    void setSpeed(int);
    void openFile();
    void saveFile();
    void showAboutInfo();
    void playSound();
    void stopSound();
    void resizeSound();
    void test();

};

#endif // MAINWINDOW_H
