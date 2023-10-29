#include "Admin_login.h"
#include "ui_Admin_login.h"
#include<QLabel>
#include<QFont>
#include<QStringList>
#include<QCompleter>
#include<QMessageBox>

AdminLogin::AdminLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminLogin)
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
    list<<"000001"<<"000002"<<"000003";
    QCompleter *com = new QCompleter(list,this);//自动提示功能
     ui->lineEdit->setCompleter(com);

     //登录字体
     ui->label->setStyleSheet("color:yellow;");
     ui->label_2->setStyleSheet("color:yellow;");

     //退出功能
      connect(ui->exit,&QPushButton::clicked,this,&QPushButton::close);
      //登录
        connect(ui->login, &QPushButton::clicked,this,&AdminLogin::checkPassword);




}
void AdminLogin::checkPassword()
{
    //获取账号密码并验证
    QString Id = ui->lineEdit->text();
    QString PW = ui->lineEdit_2->text();
    Admin.input(Id, PW);
    bool judge = Admin.verify();
    //登录功能
    if(judge)
    {

        //传输信息到下一个界面
        adminUi.setInfo(Id,PW);
        OpenAdminUi();

    }
    else QMessageBox::warning(nullptr, "Failed", "Incorrect card number or password.");
}



void AdminLogin::OpenAdminUi()
{

    this->hide();
     adminUi.show();

}


AdminLogin::~AdminLogin()
{
    delete ui;
}
