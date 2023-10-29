#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include"libraryui.h"
#include"stuloginf.h"
#include"publicui.h"



namespace Ui {
class LogInDialog;
}

class LogInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LogInDialog(QWidget *parent = nullptr);
    void OpenLibraryUi();
    void loggedIn(const QString &cardNumber, const QString &password);
    void checkPassword();
    void OpenPublic();
    ~LogInDialog();



private:
    Ui::LogInDialog *ui;
    LibraryUi libUi;
    StuLoginF stu;
    PublicUi pubUi;


};

#endif // LOGINDIALOG_H
