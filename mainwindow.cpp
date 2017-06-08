#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_dialoglogin.h"
#include "centralairconditioner.h"
//centralAirConditioner *airConditioner;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("中央空调主控机");
    UserLogin();
    this->hide();
    Init();
    timeRefresh->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UserLogin()
{
    qDebug() << __func__ << "is running.";
    QDialog dialogLogin;
    Ui::Dialog *uiDialog = new Ui::Dialog;
    uiDialog->setupUi(&dialogLogin);
    uiDialog->linePasswd->setEchoMode(QLineEdit::Password);
    dialogLogin.setWindowTitle(tr("登录"));
    dialogLogin.show();
    dialogLogin.setModal(true);
    int exec = dialogLogin.exec();
    while(exec == dialogLogin.Accepted)
    {
        if(QString::compare(uiDialog->lineUser->text(),admin.GetUser()) == 0 && QString::compare(uiDialog->linePasswd->text(),admin.GetPasswd()) == 0)
        {
            //this->show();
            //在这里的show()不生效了，只有Init那里的生效了。
            //dialogLogin.hide();
            dialogLogin.close();
            setAttribute(Qt::WA_DeleteOnClose, true);
            return ;
        }
        else
        {
            qDebug() << uiDialog->lineUser->text() << uiDialog->linePasswd->text();
            QMessageBox::warning(NULL,"warning","用户名或密码错误！");
        }
        exec = dialogLogin.exec();
    }
    if(exec == dialogLogin.Rejected)
    {
        dialogLogin.close();
        setAttribute(Qt::WA_DeleteOnClose, true);
    }
}

void MainWindow::Init()
{
    this->show();
    qDebug() << __func__ << "is running.";
    QDateTime time = QDateTime::currentDateTime();
    QString strTime = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->labelTimeDate->setText(strTime);

//    ui->spinBoxTemperature->setRange(15,35);
//    ui->spinBoxTemperature->setValue(25);
//    ui->labelDegree->setText(tr("0.0"));
//    ui->labelCost->setText(tr("0.00"));

    QStandardItemModel *model = new QStandardItemModel(this);

    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::SelectedClicked);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->resizeRowsToContents();

    //ui->tableView->resizeColumnsToContents();
    model->setRowCount(0);
    model->setHorizontalHeaderItem(0, new QStandardItem(tr("用户")));
    model->setHorizontalHeaderItem(1, new QStandardItem(tr("房间号")));
    model->setHorizontalHeaderItem(2, new QStandardItem(tr("当前温度")));
    model->setHorizontalHeaderItem(3, new QStandardItem(tr("目标温度")));
    model->setHorizontalHeaderItem(4, new QStandardItem(tr("风速")));
    model->setHorizontalHeaderItem(5, new QStandardItem(tr("工作模式")));
    model->setHorizontalHeaderItem(6, new QStandardItem(tr("连接状态")));
    model->setHorizontalHeaderItem(7, new QStandardItem(tr("能量")));
    model->setHorizontalHeaderItem(8, new QStandardItem(tr("电费")));


    QList <centralAirConditioner>::iterator i;
    for(i = airConditioner->begin(); i != airConditioner->end(); i++)
    {
        //QString tmpUser = airConditiconer->at(0).GetUser();
        int row = model->rowCount();
        model->insertRow(row);
        model->setItem(row, 0, new QStandardItem(i->GetUser()));
        model->setItem(row, 1, new QStandardItem(i->GetRoomNum()));
        model->setItem(row, 2, new QStandardItem(QString::number(i->GetTemperature(),'f',2)));
        model->setItem(row, 3, new QStandardItem(QString::number(i->GetWorkTemperature(),'f',2)));
        model->setItem(row, 4, new QStandardItem(QString::number(i->GetBlowSpeed())));
        model->setItem(row, 5, new QStandardItem(QString::number(i->GetWorkModel())));
        //model->setItem(row, 6, new QStandardItem(QString::number(i->connectionState())));
        model->setItem(row, 7, new QStandardItem(QString::number(i->GetDegree())));
        model->setItem(row, 8, new QStandardItem(QString::number(i->GetCost())));
    }


    //connect(ui->spinBox_2,SIGNAL(valueChanged(int)),this,SLOT(BlowSpeedTransfer(ui->spinBox_2->value())));
    timeRefresh = new QTimer;

    connect(timeRefresh, SIGNAL(timeout()), this, SLOT(Refresh()));

}

void MainWindow::Refresh()
{
    //ui->labelDegree->setText(QString::number(airConditioner.GetDegree(),'f',1));
    //ui->labelCost->setText(QString::number(airConditioner.GetCost(),'f',2));
    QDateTime time = QDateTime::currentDateTime();
    QString strTime = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->labelTimeDate->setText(strTime);

    ui->tableView->repaint();
}
