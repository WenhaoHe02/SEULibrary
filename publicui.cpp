#include "publicui.h"
#include "ui_publicui.h"
#include<QPixmap>
#include <QTableView>
#include<QStandardItemModel>
#include"logindialog.h"
#include<QMessageBox>
#include<QDebug>
#include<QSqlError>
#include<QSqlTableModel>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDateTime>
#include<QDebug>

PublicUi::PublicUi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PublicUi)
{
    ui->setupUi(this);
    //表格设计
    ui->tableView_3->horizontalHeader()->setStyleSheet(R"(
        QHeaderView::section {
            background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(51, 153, 255,1), stop:1 rgba(52, 246, 177,1));
            color: white;
            border: none;
            font-size: 20px;
            font-family: "微软雅黑";
            padding-top: 5;
            padding-bottom: 5;
        }
    )");
    ui->tableView_3->verticalHeader()->setStyleSheet(R"(
        QHeaderView::section {
            background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(51, 153, 255,1), stop:1 rgba(52, 246, 177,1));
            color: white;
            border: none;
            font-size: 20px;
            font-family: "微软雅黑";
        }
    )");
    ui->tableView_3->viewport()->setStyleSheet("background-color: lightblue;");
    ui->tableView_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableView_3->resizeRowsToContents();
    ui->tableView_3->resizeColumnsToContents();
    ui->tableView_3->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers); // 不允许编辑


    //初始化数据库
            db2_00 = QSqlDatabase::addDatabase("QMYSQL", "connection2_00");
           //连接数据库
           db2_00.setHostName("127.0.0.1");
           db2_00.setUserName("HWH");
           db2_00.setPassword("@MySql668931hwh");
           db2_00.setDatabaseName("login");
           if(!db2_00.open())//数据库打开失败
           {
               QMessageBox::warning(this,"错误",db2_00.lastError().text());
               qDebug()<<db2_00.lastError().text();
               return;
           }

           model = new QSqlTableModel(this,db2_00);
           model->setTable("books");
           ui->tableView_3->setModel(model);
           model->select();
           //查询
           // 设置下拉列表的内容
           ui->comboBox->addItems(QStringList() << "书名" << "作者名" << "ISBN" << "索书号" << "出版社"<<"丛书名");
           // 连接查询按钮的点击事件到查询函数
           connect(ui->pushButton_9, &QPushButton::clicked, this, &PublicUi::searchBook);
}
void  PublicUi::searchBook()
{
    QString searchType = ui->comboBox->currentText();
        QString searchText = ui->lineEdit->text();

        QString queryString;

        if (searchType == "书名") {
            queryString = "书名 LIKE '%" + searchText + "%'";
        } else if (searchType == "作者名") {
            queryString = "作者名 LIKE '%" + searchText + "%'";
        } else if (searchType == "书目编号") {
            queryString = "书目编号 = '" + searchText + "'";
        } else if (searchType == "索书号") {
            queryString = "索书号  LIKE '%" + searchText + "%'";
        } else if (searchType == "出版社") {
            queryString = "出版社 LIKE '%" + searchText + "%'";
        }else if (searchType == "丛书名") {
            queryString = " 丛书名 LIKE '%" + searchText + "%'";
        }


        model->setFilter(queryString);
        model->select();

}

PublicUi::~PublicUi()
{
    delete ui;
}
