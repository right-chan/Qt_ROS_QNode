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
    this->setStyleSheet("background-color: green;");
    ui->setupUi(this);
    
//  이미지
    QPixmap *pix;
    pix = new QPixmap("/home/chan/catkin_ws/src/qt_test/src/dice.png");
    int w = ui->imglabel1->width();
    int h = ui->imglabel1->height();
    ui->imglabel1->setPixmap(pix->scaled(w,h,Qt::KeepAspectRatio));
    ui->imglabel1->show();

//  움짤 QMovie .gif
    movie  = new QMovie("/home/chan/catkin_ws/src/qt_test/src/dice.png");
    QMovie *movie2 = new QMovie("/home/chan/catkin_ws/src/qt_test/src/loading.gif");
    movie2->setScaledSize(this->ui->imglabel3->size());
    ui->imglabel2->setMovie(movie2);
    // movie2->setSpeed(200);
    // ui->imglabel2->resize(1920,1080);
    // ui->imglabel2->showFullScreen();
    // label.setMovie(movie2);
    label = new QLabel(this);
    label->setMovie(movie2);
    label->setGeometry(1000,0,480,300);
    movie2->start();
    



//  mp4
    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    player->setMedia(QUrl::fromLocalFile("/home/chan/catkin_ws/src/qt_test/src/strawberry moon.mp4"));
    player->setVideoOutput(vw);
    vw->setGeometry(300,300,1920,1080);
    // vw->setFullScreen(true);
    // player->play();
    // player->stop();

    QObject::connect(&qnode, SIGNAL(msgSubscribed()), this, SLOT(updateSubBox()));
    QObject::connect(ui->exitbutton, &QPushButton::clicked, this, &QApplication::quit);
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
    // int msg = outQString.toInt;
    switch(outQString.toInt())
    {
        case 1:
        std::cout<<"case 1"<<std::endl;
        player->play();

        break;
        case 2:
        std::cout<<"case 2"<<std::endl;
        player->stop();
        break;
        case 3:
        std::cout<<"case 3"<<std::endl;
        player->pause();
        break;
        case 4:
        std::cout<<"case 4"<<std::endl;
        label->setMovie(movie);
        movie->start();
        break;
        case 5:
        std::cout<<"case 5"<<std::endl;
        player->pause();
        break;
        case 6:
        std::cout<<"case 6"<<std::endl;
        player->pause();
        break;
        default:
        std::cout<<"deafult"<<std::endl;
        break;
    }
    
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