#ifndef BOOKS_H
#define BOOKS_H

#include <QObject>
#include <QString>

class Books:public QObject
{
    Q_OBJECT

private:
    QString book_numb;
    QString book_name;
    QString author_numb;
    QString author_name;
    QString publisher_numb;
    QString publisher_name;
    int storage_now;
    int storage_all;

public:
    Books(QString &bnumb=QString("#"),QString &bname=QString("#"),
          QString &anumb=QString("#"),QString &aname=QString("#"),
          QString &pnumb=QString("#"),QString &pname=QString("#"),
          int s_now=0,int s_all=0);

    Books(const Books &p);

    void Set_Book_Numb(QString &bnumb);
    void Set_Book_Name(QString &bname);
    void Set_Author_Numb(QString &anumb);
    void Set_Author_Name(QString &aname);
    void Set_Publisher_Numb(QString &pnumb);
    void Set_Publisher_Name(QString &pname);
    void Set_Storage_Now(int i);
    void Set_Storage_All(int i);

    QString &Get_Book_Numb();
    QString &Get_Book_Name();
    QString &Get_Author_Numb();
    QString &Get_Author_Name();
    QString &Get_Publisher_Numb();
    QString &Get_Publisher_Name();
    int Get_Storage_now();
    int Get_Storage_all();

};

#endif // BOOKS_H
