#include "stuloginf.h"
#include<QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include<QDebug>
#include <QMessageBox>
StuLoginF::StuLoginF()
{


}
void StuLoginF::input(QString Id, QString PW)
{
    stuId = Id;
    stuPassword = PW;
}
StuLoginF:: ~StuLoginF()
{

}
QString StuLoginF:: getId()
{
    return stuId;
}
QString StuLoginF:: getPW()
{
    return  stuPassword;
}
bool StuLoginF::verify()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","connection1");
    //连接数据库
    db.setHostName("127.0.0.1");
    db.setUserName("HWH");
    db.setPassword("@MySql668931hwh");
    db.setDatabaseName("login");
    //打开数据库
    if(!db.open())//数据库打开失败
    {
        qDebug()<<db.lastError().text();
        return false;

    }
    else
    {
        QSqlQuery query(db);
        query.prepare("SELECT * FROM stuinfo WHERE 一卡通号 = :some_value AND 密码 = :some_password");
          query.bindValue(":some_value", stuId);
          query.bindValue(":some_password", stuPassword);
            if (!query.exec())
            {
                    // 处理查询失败的情况
                    QMessageBox::warning(nullptr, "Error", "Query failed: " + query.lastError().text());
                    qDebug()<<query.lastError().text();
                    return false;
                }


            if (query.next()) {
                // 如果查询有结果，说明有匹配的一卡通号和密码
                db.close();
                QSqlDatabase::removeDatabase("connection1");
                return true;

            }
            // 没有找到匹配的一卡通号和密码
            return false;


    }


}
