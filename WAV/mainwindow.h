#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

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
signals:
    void speedChanged(double);
private slots:
    void setSpeed(int);
    void openFile();
    void saveFile();
    void showAboutInfo();

};

#endif // MAINWINDOW_H
