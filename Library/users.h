#ifndef USERS_H
#define USERS_H

#include<QObject>
#include<QString>
#include<QList>
#include<QStringList>

#include "books.h"

class Users:public QObject
{

    Q_OBJECT

private:
    QString user_name;
    QString user_id;
    QString user_password;

    bool administrable;

    int borrow_books_numb;

    QStringList borrow_books;//存书名号，再通过查找

    //已借图书

public:
    Users(QString &name=QString("0"),
          QString &id=QString("0"),
          QString &password=QString("000000"),
          bool administer=false,
          int books_numb=0);

    Users(const Users &p);

    void Set_name(QString &name=QString("0"));
    void Set_id(QString &id=QString("0"));
    void Set_password(QString &password=QString("000000"));
    void Set_administer(bool administer);//设置该用户为管理员
    void Set_Books_Numb(int numb);
    void Add_Books(const QString &book_id);
    void Erase_Books(const QString& bnumb);

    QString &Get_name();
    QString &Get_id();
    QString &Get_password();
    bool is_administrable();
    int Get_Books_Numb();
    QString Get_Books(int i);

};

#endif // USERS_H
