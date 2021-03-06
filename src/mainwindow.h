#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QtWidgets>

#include "qnode.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int argc, char** argv, QWidget *parent = 0);
    ~MainWindow();
    QString toQString(std::string const &s);
    std::string fromQString(QString const &s);

private:
    Ui::MainWindow *ui;
    QNode qnode;

    QVideoWidget * vw;
    QMediaPlayer * player;   
    QLabel * label;
    QLabel * eye;
    QMovie * eyemovie;
    QMovie *movie;
    QMovie *movie2;
    QPixmap *pix;

public slots:
    void updateSubBox();
};

#endif // MAINWINDOW_H
