#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

#include <QMediaPlayer>
#include <QVideoWidget>

MainWindow::MainWindow(int argc, char** argv, QWidget *parent) :
    QMainWindow(parent), qnode(argc, argv),
    ui(new Ui::MainWindow)
{
    qnode.init();
    ui->setupUi(this);
//  이미지
    QPixmap pix("/home/chan/catkin_ws/src/qt_test/src/dice.png");
    int w = ui->imglabel1->width();
    int h = ui->imglabel1->height();
    ui->imglabel1->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
//  움짤 QMovie .gif
    QMovie *movie = new QMovie("/home/chan/catkin_ws/src/qt_test/src/rotating_earth.gif");
    ui->imglabel2->setMovie(movie);
    movie->start();
//  mp4
    QMediaPlayer * player = new QMediaPlayer;
    QVideoWidget * vw = new QVideoWidget;
    player->setVideoOutput(vw);
    player->setMedia(QUrl::fromLocalFile("/home/chan/catkin_ws/src/qt_test/src/strawberry moon.mp4"));

    vw->setGeometry(100,100,300,400);
    vw->show();
    player->play();

    QObject::connect(&qnode, SIGNAL(msgSubscribed()), this, SLOT(updateSubBox()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// convert to std::string to QString
QString MainWindow::toQString(std::string const &s)
{
    return QString::fromUtf8(s.c_str());
}
// convert from QString to std::string
std::string MainWindow::fromQString(QString const &s)
{
    return std::string(s.toUtf8().constData());
}

// updated subscribed data to subText text view box
void MainWindow::updateSubBox(){
    std::string subbed_msg = qnode.sub_message;
    QString outQString = toQString(subbed_msg);
    ui->subText->setPlainText(outQString);
}

// publish text written on the input text box when button is pressed
void MainWindow::on_publishButton_clicked()
{
    std_msgs::String pub_msg;
    QString inputQString = ui->pubText->toPlainText();
    std::string inputString = fromQString(inputQString);
    qnode.pub_message = inputString;
    pub_msg.data = inputString;
    qnode.pub.publish(pub_msg);
}
