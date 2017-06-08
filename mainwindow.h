#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDateTime>
#include <QTimer>
#include <QDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QMap>
#include <centralairconditioner.h>
//#include <QObject>

//class centralAirConditioner;
//centralAirConditioner *airConditioner;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Init();
    void UserLogin();

public slots:
    void Refresh();
//    void RevDateFromDB(QString user, QString roomNum, float temperature, float workTemperature, \
//                int blowSpeed, int workModel, int connectionState, float degree, float cost);

private slots:
    //void PushButtonStartClicked();

signals:
    void TimeStartSignal();
    void TimeStopSignal();

private:
    Ui::MainWindow *ui;
    QTimer *timeRefresh;
};

#endif // MAINWINDOW_H
