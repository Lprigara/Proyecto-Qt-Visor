#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QLabel>
#include <QPixmap>
#include <QWaitCondition>
#include <QMutex>
#include <QMovie>
#include <QSettings>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialog.h"

bool paused = true;  //variable para parar/pausar

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    movie=NULL;

    settings = new QSettings("Leonor", "viewer"); //configura QSetting
    ui->autoinicio->setChecked(settings->value("viewer/autoinicio").toBool()); //setChecked necesita un bool como arg.
}

MainWindow::~MainWindow()
{
    delete ui;
    delete movie;
}


void MainWindow::on_actionAbrir_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Abrir archivo", QString() ,"Video (*.mjpeg)"); //te devuelve el nombre del archivo
    if(!fileName.isEmpty()) {
        QPixmap foto(fileName);
        if(foto.isNull()) {
            QMessageBox::information(this, "Abrir archivo", "El archivo no pudo ser abierto. ");
        }
        else {
            movie = new QMovie(fileName);
            ui->label->setMovie(movie);
               //connect(movie_, SIGNAL(updated(const QRect&)), this, SLOT(on_MovieUpdated(const QRect&)));
            if(ui->autoinicio->isChecked())
                movie->start();

        }//else
    }//if
}//funcion


void MainWindow::on_start_clicked()
{
    if(!paused){
        movie->setPaused(1);
        paused = true;
    }
    else{
        movie->start();
        paused = false;
    }
}

void MainWindow::on_stop_clicked()
{
    movie->stop();
    paused = true;
}

void MainWindow::on_exit_clicked()
{
    qApp->quit(); //qApp = QApplication del main
}

void MainWindow::on_actionSalir_triggered()
{
    qApp->quit();
}

void MainWindow::on_autoinicio_stateChanged(int arg1)
{
    settings->setValue("viewer/autoinicio", ui->autoinicio->isChecked());
}

void MainWindow::on_actionAcerca_de_triggered()
{
    Dialog acercaDe(this);
    acercaDe.exec();
}

/*
void MovieViewerWindow::showFrame(const QRect& rect)
{
    QPixmap pixmap = movie_->currentPixmap();
    ui->label->setPixmap(pixmap);
}
*/
