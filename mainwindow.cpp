#include "mainwindow.h"
#include "ui_mainwindow.h"




#include<QMovie>
#include <QPushButton>
#include <QFont>
#include<QPicture>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置背景动图
    QMovie *gif1 = new QMovie(":/new/prefix3/SEU1.gif");
    ui->picture1->setMovie(gif1);
    gif1->start();

    //设置按钮大小
    ui->Stu->resize(300,150);
    ui->Admin->resize(300,150);
    //背景 字体颜色
    ui->Stu->setStyleSheet("QPushButton{color:yellow;"
                             "background-color:green;"
                             "}");
    ui->Admin->setStyleSheet("QPushButton{color:green;"
                             "background-color:yellow;"
                             "}");
    ui->pushButton->setStyleSheet("QPushButton{color:green;"
                             "background-color:yellow;"
                             "}");
    // 字体
    QFont font;
    font.setBold(true);
    font.setPointSize(28);
    ui->Stu->setFont(font);
    ui->Admin->setFont(font);
    ui->pushButton->setFont(font);

    //校徽居中

    ui->Picture2->setAlignment(Qt::AlignCenter);

    //标题
    ui->Title->setAlignment(Qt::AlignCenter);
    font.setPointSize(40);
    ui->Title->setFont(font);

    //页面跳转
    connect(ui->Stu,&QPushButton::clicked,this,&MainWindow::changeWin);
    connect(ui->Admin,&QPushButton::clicked,this,&MainWindow::changeWinAdmin);
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::changeWinBuyer);





}

void MainWindow::changeWin()
{
     dialog3.close();
    dialog2.close();
    this->hide();
    dialog1.show();

}
void MainWindow::changeWinAdmin()
{
     dialog1.close();
     dialog3.close();
    this->hide();
    dialog2.show();

}
void MainWindow::changeWinBuyer()
{
     dialog1.close();
     dialog2.close();
     this->hide();
     dialog3.show();

}
MainWindow::~MainWindow()
{
    delete ui;
}

