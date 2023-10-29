#ifndef BUYERLOGIN_H
#define BUYERLOGIN_H

#include <QDialog>
#include"adminloginf.h"
#include"buyerui.h"

namespace Ui {
class BuyerLogin;
}

class BuyerLogin : public QDialog
{
    Q_OBJECT

public:
    explicit BuyerLogin(QWidget *parent = nullptr);
    void OpenBuyerUi();
    void loggedIn(const QString &cardNumber, const QString &password);
    void checkPassword();
    ~BuyerLogin();

private:
    Ui::BuyerLogin *ui;
    Adminloginf Admin;
    BuyerUi buyerUi;
};

#endif // BUYERLOGIN_H
