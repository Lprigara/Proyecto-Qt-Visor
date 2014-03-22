#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_exit_clicked();

    void on_actionSalir_triggered();

    void on_actionAbrir_triggered();

    void on_start_clicked();

    void on_stop_clicked();

    void on_autoinicio_stateChanged(int arg1);

    void on_actionAcerca_de_triggered();

    //void showFrame(const QRect& rect);

private:
    Ui::MainWindow *ui;
    QMovie *movie;
    QSettings *settings;
};

#endif // MAINWINDOW_H
