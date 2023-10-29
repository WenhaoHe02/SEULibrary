#ifndef BUYERUI_H
#define BUYERUI_H

#include <QMainWindow>
#include<QSqlTableModel>
#include<QString>

namespace Ui {
class BuyerUi;
}

class BuyerUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit BuyerUi(QWidget *parent = nullptr);
    void add();
    void Delete();
    void confirm();
    void cancel();
    void searchBook();
    ~BuyerUi();

private:
    Ui::BuyerUi *ui;
    QSqlDatabase db2_0;
    QSqlTableModel *model;
    QSqlTableModel *model2;
    QSqlTableModel *model3;
    QSqlQuery*query;
};

#endif // BUYERUI_H
