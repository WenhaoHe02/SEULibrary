#include "logindialog.h"
#include "ui_logindialog.h"
#include<QLabel>
#include<QFont>
#include<QStringList>
#include<QCompleter>
#include<QMessageBox>
#include<QDebug>
#include"stuloginf.h"
#include"publicui.h"

LogInDialog::LogInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogInDialog)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);

    // 设置背景图片
        QPixmap background(":/new/prefix3/SEU3.jpg");  // 从资源文件中加载图片
        background = background.scaled(this->size(), Qt::IgnoreAspectRatio);  // 调整图片大小以适应窗口
        QPalette palette;
        palette.setBrush(QPalette::Background, background);
        this->setPalette(palette);

    //标题字体居中
    ui->label_4->setAlignment(Qt::AlignCenter);
    //字体
    QFont font;
    font.setBold(true);
    font.setPointSize(30);
    ui->label_4->setFont(font);

    //账号提示
    QStringList list;
    list<<"213223200"<<"213223201"<<"213223202"<<"213223203"<<"213223204";
    QCompleter *com = new QCompleter(list,this);//自动提示功能
     ui->lineEdit->setCompleter(com);

     //登录字体
     ui->label->setStyleSheet("color:yellow;");
     ui->label_2->setStyleSheet("color:yellow;");

     //退出功能
      connect(ui->exit,&QPushButton::clicked,this,&QPushButton::close);
      connect(ui->login, &QPushButton::clicked,this,&LogInDialog::checkPassword);
      connect(ui->pushButton, &QPushButton::clicked,this,&LogInDialog::OpenPublic);
}


void LogInDialog::checkPassword()
{
    //获取账号密码并验证
    QString Id = ui->lineEdit->text();
    QString PW = ui->lineEdit_2->text();
    stu.input(Id, PW);
    bool judge = stu.verify();
    //登录功能
    if(judge)
    {

        //传输信息到下一个界面
        libUi.setInfo(Id,PW);
        OpenLibraryUi();

    }
    else QMessageBox::warning(nullptr, "Failed", "Incorrect card number or password.");
}



void LogInDialog::OpenLibraryUi()
{

    this->hide();
     libUi.show();

}
void LogInDialog::OpenPublic()
{
    this->hide();
   pubUi.show();

}
LogInDialog::~LogInDialog()
{
    if (QSqlDatabase::contains("connection1"))
        {
            QSqlDatabase::database("connection1").close();
            QSqlDatabase::removeDatabase("connection1");
        }
    delete ui;
}

