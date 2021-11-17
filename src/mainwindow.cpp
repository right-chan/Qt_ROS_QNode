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
    this->setStyleSheet("background-color: black;");
    ui->setupUi(this);

    QCursor cursor(Qt::BlankCursor); // 커서숨기기
    QApplication::setOverrideCursor(cursor);
    QApplication::changeOverrideCursor(cursor);
    label = new QLabel(this);
    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);

    //// 디폴트 눈 깜빡이기

    eyemovie = new QMovie("/home/chan/catkin_ws/src/qt_test/src/eye10.gif");
    ui->eyeLabel->setGeometry(0,0,1920,1080);
    ui->eyeLabel->setMovie(eyemovie);
    eyemovie->setScaledSize(ui->eyeLabel->size());
    eyemovie->start();
/////////////////////////////////////////////////////////
    

    pix = new QPixmap("/home/chan/catkin_ws/src/qt_test/src/dice.png");
    movie  = new QMovie("/home/chan/catkin_ws/src/qt_test/src/Spinner-1s-200px.gif");
    movie2 = new QMovie("/home/chan/catkin_ws/src/qt_test/src/eye10.gif");

    
    // label->setMovie(movie);
    // label->setGeometry(0,0,1920,1080);
    // label->show();
    // movie->setScaledSize(label->size());
    // movie->start();


    player->setMedia(QUrl::fromLocalFile("/home/chan/catkin_ws/src/qt_test/src/strawberry moon.mp4"));
    player->setVideoOutput(vw);
    // 소리는 player에서만 나옴
    QObject::connect(&qnode, SIGNAL(msgSubscribed()), this, SLOT(updateSubBox()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



// updated subscribed data to subText text view box
void MainWindow::updateSubBox(){
    std::string subbed_msg = qnode.sub_message;
    QString outQString = toQString(subbed_msg);
    // int msg = outQString.toInt;
    switch(outQString.toInt())
    {
        case 1:
            label->close();
            vw->show();
            vw->setGeometry(0,0,1920,1080);            
            player->play();
        break;

        case 2:
            std::cout<<"case 2"<<std::endl;
            vw->close();
            player->stop();
        break;

        case 3:
            std::cout<<"case 3"<<std::endl;
            vw->setGeometry(0,0,1920,1080);
            player->pause();
        break;

        case 4:
            label->show();
            vw->close();   
            player->stop();            
            std::cout<<"case 4"<<std::endl;
            label->setGeometry(0,0,1920,1080);

            label->setMovie(movie);
            movie->setScaledSize(label->size());
            movie->start();
        break;

        case 5:
            label->show();
            vw->close();
            player->stop();
            label->setGeometry(0,0,1920,1080);
            std::cout<<"case 5"<<std::endl;
            
            label->setMovie(movie2);
            movie2->setScaledSize(label->size());
            movie2->start();
        break;

        case 6:
            label->show();
            std::cout<<"case 6"<<std::endl;
            vw->close();
            player->stop();
            label->setGeometry(0,0,1920,1080);
            label->setPixmap(pix->scaled(label->width(),label->height(),Qt::KeepAspectRatio));
        break;

        default:
            std::cout<<"deafult"<<std::endl;
        break;
    }
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