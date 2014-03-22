#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "acerca.h"
#include "preferencias.h"


bool Paused = true;  //variable para parar/pausar

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    movie_=NULL;
    camera_=NULL;
    viewfinder_=NULL;
    captureB_=NULL;

    setting_ = new QSettings("Leonor", "viewer"); //configura QSetting
    ui_->autoinicio->setChecked(setting_->value("viewer/autoinicio",true).toBool()); //setChecked necesita un bool como arg.

    devices_=QCamera::availableDevices();
    dispdefault_ = setting_->value("viewer/deviceDefault",devices_[0]).toByteArray();
    dispchoise_ = setting_->value("viewer/deviceChoise",dispdefault_).toByteArray();
}

MainWindow::~MainWindow()
{
    delete ui_;
    delete movie_;
    delete camera_;
    delete viewfinder_;
    delete setting_;
    delete captureB_;
}


//Funcion para abrir archivo de video
void MainWindow::on_actionAbrir_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Abrir archivo", QString() ,"Video (*.mjpeg)"); //te devuelve el nombre del archivo
    if(!fileName.isEmpty()) {
        QPixmap foto(fileName);
        if(foto.isNull()) {
            QMessageBox::information(this, "Abrir archivo", "El archivo no pudo ser abierto. ");
        }
        else {
            movie_ = new QMovie(fileName);
            ui_->label->setMovie(movie_);
            if(ui_->autoinicio->isChecked())
                movie_->start();

        }//endelse
    }//endif
}

void MainWindow::on_actionCapturar_triggered()
{ 
    qDebug()<<dispdefault_<<dispchoise_;
     if(operator!= (dispdefault_,dispchoise_)){  
        camera_->stop();
        delete camera_;
        camera_ = new QCamera(dispchoise_);
     }
     else{
        camera_ = new QCamera(dispdefault_);
     }

     captureB_ = new captureBuffer;
     camera_->setViewfinder(captureB_);

    //objeto que emite la señal, señal emitida, objeto que recibe la señal, accion que desencadena esa señal
     connect(captureB_, SIGNAL(signalImage(QImage)), this, SLOT(image1(QImage)));

     camera_->setCaptureMode(QCamera::CaptureViewfinder);
     camera_->start();
}

void MainWindow::image1(QImage image){

    //Modificar (pintar) la imagen para imprimirla en el label
    QTime time;
    QTime currenTime= time.currentTime();
    QString stringTime=currenTime.toString();

    QPixmap pixmap(QPixmap::fromImage(image));

    QPainter painter(&pixmap);
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 25));
    painter.drawText(0, 0,pixmap.width(), pixmap.height(), Qt::AlignBottom, stringTime,0);

    ui_->label->setPixmap(pixmap);
}

void MainWindow::on_start_clicked()
{
    if(!Paused){
        movie_->setPaused(1);
        Paused = true;
    }
    else{
        movie_->start();
        Paused = false;
    }
}

void MainWindow::on_stop_clicked()
{
    movie_->stop();
    Paused = true;
}

void MainWindow::on_exit_clicked()
{
    qApp->quit(); //qApp = QApplication del main
}

void MainWindow::on_actionSalir_triggered()
{
    qApp->quit();
}

void MainWindow::on_autoinicio_stateChanged(int)
{
    setting_->setValue("viewer/autoinicio", ui_->autoinicio->isChecked());
}

void MainWindow::on_actionAcerca_de_triggered()
{
    Acerca acercaDe(this);
    acercaDe.exec();
}

void MainWindow::on_actionPreferencias_triggered()
{
   Preferencias prefe(this);
   prefe.exec();
}
