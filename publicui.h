#ifndef PUBLICUI_H
#define PUBLICUI_H

#include <QMainWindow>
#include<QSqlTableModel>
#include<QString>

namespace Ui {
class PublicUi;
}

class PublicUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit PublicUi(QWidget *parent = nullptr);
    ~PublicUi();

private:
    Ui::PublicUi *ui;
    QSqlDatabase db2_00;
    QSqlTableModel *model;
     void searchBook();

};

#endif // PUBLICUI_H
