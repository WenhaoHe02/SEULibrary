#ifndef LIBRARYUI_H
#define LIBRARYUI_H
#include<QSqlTableModel>

#include <QMainWindow>
#include<QString>



namespace Ui {
class LibraryUi;
}

class LibraryUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit LibraryUi(QWidget *parent = nullptr);
    void setInfo(const QString&cardnumber,const QString&password);
    void displayStudentInfo();
    void initializeDb();
    void searchBook();
    void reserveBook();
    void updateCurrentStatus();
    void reportLostBook();
    void recommend();
    void borrowAgain();

    ~LibraryUi();
private:
    Ui::LibraryUi *ui;
    QString cardnumber;
    QString password;
    QSqlQueryModel  *queryModel;
    QSqlTableModel* model4x;
    QSqlDatabase db2;
    QSqlQuery *query3;
    QSqlQuery *query4;
    QSqlQuery *query5;

};

#endif // LIBRARYUI_H
