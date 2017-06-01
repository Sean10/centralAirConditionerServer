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
         //这里不应该这样提示，这是用户注册的提示，而不是管理员的提示
//        else if(!QString::compare(uiDialog->lineUser->text(),admin.GetUser()))
//        {
//            QMessageBox::warning(NULL,"warning","用户名不存在！");
//        }
        else// if(!QString::compare(uiDialog->linePasswd->text(),admin.GetPasswd()))
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

void MainWindow::PushButtonStartClicked()
{
    qDebug() << __func__ << "is running.";
    if(ui->pushButtonStart->text() == tr("开启"))
    {
        ui->pushButtonStart->setText(tr("关闭"));
        //开启从控机
        emit TimeStartSignal();

    }
    else if(ui->pushButtonStart->text() == tr("关闭"))
    {
        ui->pushButtonStart->setText(tr("开启"));
        //关闭从控机
        emit TimeStopSignal();


    }
}

void MainWindow::Init()
{
    this->show();
    qDebug() << __func__ << "is running.";
    QDateTime time = QDateTime::currentDateTime();
    QString strTime = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->labelTimeDate->setText(strTime);

    ui->spinBoxTemperature->setRange(15,35);
    ui->spinBoxTemperature->setValue(25);
    ui->labelDegree->setText(tr("0.0"));
    ui->labelCost->setText(tr("0.00"));


    //connect(ui->spinBox_2,SIGNAL(valueChanged(int)),this,SLOT(BlowSpeedTransfer(ui->spinBox_2->value())));
    timeRefresh = new QTimer;

    connect(timeRefresh, SIGNAL(timeout()), this, SLOT(Refresh()));
    connect(ui->pushButtonStart,SIGNAL(clicked()), this,SLOT(PushButtonStartClicked()));
}

void MainWindow::Refresh()
{
    ui->labelDegree->setText(QString::number(airConditioner.GetDegree(),'f',1));
    ui->labelCost->setText(QString::number(airConditioner.GetCost(),'f',2));
    QDateTime time = QDateTime::currentDateTime();
    QString strTime = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->labelTimeDate->setText(strTime);
}
