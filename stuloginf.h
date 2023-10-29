#ifndef STULOGINF_H
#define STULOGINF_H
#include<QString>

class StuLoginF
{
public:
    StuLoginF();
    void input(QString Id, QString PW);
    ~StuLoginF();
    bool verify();
    QString getId();
    QString getPW();

private:
    QString stuId;
    QString stuPassword;


};



#endif // STULOGINF_H
