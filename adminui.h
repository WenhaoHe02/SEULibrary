#ifndef ADMINUI_H
#define ADMINUI_H

#include <QMainWindow>
#include<QSqlTableModel>
#include<QString>


namespace Ui {
class AdminUi;
}

class AdminUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminUi(QWidget *parent = nullptr);
    void searchBook();
    void setInfo(const QString&Id,const QString&password);
    void add();
    void Delete();
    void confirm();
    void cancel();
    void borrowBook();
   void returnBook();

    ~AdminUi();

private:
    Ui::AdminUi *ui;
    QString Id;
    QString password;
    QSqlDatabase db2_;
    QSqlTableModel *model;
    QSqlTableModel *model2;
    QSqlTableModel *model3;
    QSqlQuery*query;
    QSqlQuery*query2;
    QSqlQuery*query3;

};

#endif // ADMINUI_H
