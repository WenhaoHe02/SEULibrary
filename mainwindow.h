#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"logindialog.h"
#include"Admin_login.h"
#include"buyerlogin.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void changeWin();
    void changeWinAdmin();
    void changeWinBuyer();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LogInDialog dialog1;
    AdminLogin dialog2;
    BuyerLogin dialog3;
};
#endif // MAINWINDOW_H
