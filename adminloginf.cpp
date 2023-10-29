#include "adminloginf.h"
#include<QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include<QDebug>
#include <QMessageBox>
Adminloginf::Adminloginf()
{


}
void Adminloginf::input(QString Id, QString PW)
{
    AdminId = Id;
    AdminPassword = PW;
}
bool Adminloginf::verify()
{
    QSqlDatabase db_ = QSqlDatabase::addDatabase("QMYSQL","connection1_");
    //连接数据库
    db_.setHostName("127.0.0.1");
    db_.setUserName("HWH");
    db_.setPassword("@MySql668931hwh");
    db_.setDatabaseName("login");
    //打开数据库
    if(!db_.open())//数据库打开失败
    {
        qDebug()<<db_.lastError().text();
        return false;

    }
    else
    {
        QSqlQuery query(db_);
        query.prepare("SELECT * FROM admin WHERE 管理员账号 = :some_value AND 密码 = :some_password");
          query.bindValue(":some_value", AdminId);
          query.bindValue(":some_password", AdminPassword);
            if (!query.exec())
            {
                    // 处理查询失败的情况
                    QMessageBox::warning(nullptr, "Error", "Query failed: " + query.lastError().text());
                    qDebug()<<query.lastError().text();
                    return false;
                }


            if (query.next()) {
                // 如果查询有结果，说明有匹配的账号和密码
                db_.close();
                QSqlDatabase::removeDatabase("connection1");
                return true;

            }
            // 没有找到匹配的账号和密码
            return false;


    }


}
