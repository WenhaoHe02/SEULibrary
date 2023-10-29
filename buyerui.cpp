#include "buyerui.h"
#include "ui_buyerui.h"
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

BuyerUi::BuyerUi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BuyerUi)
{
    ui->setupUi(this);
    //表格1设计
    ui->tableView->horizontalHeader()->setStyleSheet(R"(
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
    ui->tableView->verticalHeader()->setStyleSheet(R"(
        QHeaderView::section {
            background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(51, 153, 255,1), stop:1 rgba(52, 246, 177,1));
            color: white;
            border: none;
            font-size: 20px;
            font-family: "微软雅黑";
        }
    )");
    ui->tableView->viewport()->setStyleSheet("background-color: lightblue;");
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    //初始化数据库
            db2_0 = QSqlDatabase::addDatabase("QMYSQL", "connection2_0");
           //连接数据库
           db2_0.setHostName("127.0.0.1");
           db2_0.setUserName("HWH");
           db2_0.setPassword("@MySql668931hwh");
           db2_0.setDatabaseName("login");
           if(!db2_0.open())//数据库打开失败
           {
               QMessageBox::warning(this,"错误",db2_0.lastError().text());
               qDebug()<<db2_0.lastError().text();
               return;
           }

           model = new QSqlTableModel(this,db2_0);
           model->setTable("books");
           ui->tableView->setModel(model);
           model->select();
           //查询
           // 设置下拉列表的内容
           ui->comboBox->addItems(QStringList() << "书名" << "作者" << "ISBN" << "索书号" << "出版社"<<"丛书名");
           // 连接查询按钮的点击事件到查询函数
           connect(ui->pushButton_8, &QPushButton::clicked, this, &BuyerUi::searchBook);
    //增删改
    connect(ui->pushButton_4, &QPushButton::clicked, this, &BuyerUi::add);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &BuyerUi::Delete);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &BuyerUi::confirm);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &BuyerUi::cancel);
}
void BuyerUi::add()
{
    int newRow = model->rowCount();
    model->insertRow(newRow);
    ui->tableView->selectRow(newRow);
    ui->tableView->setFocus();
}
void BuyerUi::Delete()
{
    QItemSelectionModel *select = ui->tableView->selectionModel();
    if (select->hasSelection())
    {
        model->removeRow(select->currentIndex().row());
    }
}
void BuyerUi::confirm()
{
    model->submitAll();
}
void BuyerUi::cancel()
{
    model->revertAll();
}
void  BuyerUi::searchBook()
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
BuyerUi::~BuyerUi()
{
    delete ui;
}
