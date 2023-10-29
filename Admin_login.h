#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H
#include"adminloginf.h"
#include"adminui.h"
#include <QDialog>


namespace Ui {
class AdminLogin;
}

class AdminLogin : public QDialog
{
    Q_OBJECT

public:
    explicit AdminLogin(QWidget *parent = nullptr);
    void OpenAdminUi();
    void loggedIn(const QString &cardNumber, const QString &password);
    void checkPassword();
    ~AdminLogin();

private:
    Ui::AdminLogin *ui;
    Adminloginf Admin;
    AdminUi adminUi;

};

#endif // LOGINDIALOG_H
