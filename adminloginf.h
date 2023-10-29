#ifndef ADMINLOGINF_H
#define ADMINLOGINF_H
#include<QString>

class Adminloginf
{
public:
    Adminloginf();

    void input(QString Id, QString PW);
    bool verify();
private:
    QString AdminId;
    QString AdminPassword;

};

#endif // ADMINLOGINF_H
