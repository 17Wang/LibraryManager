#include <QObject>

#include "books.h"

Books::Books(QString &bnumb, QString &bname, QString &anumb, QString &aname, QString &pnumb, QString &pname, int s_now, int s_all)
{
    book_name=bname;
    book_numb=bnumb;
    author_name=aname;
    author_numb=anumb;
    publisher_name=pname;
    publisher_numb=pnumb;
    storage_now=s_now;
    storage_all=s_all;
}

Books::Books(const Books &p)
{
    book_name=p.book_name;
    book_numb=p.book_numb;
    author_name=p.author_name;
    author_numb=p.author_numb;
    publisher_name=p.publisher_name;
    publisher_numb=p.publisher_numb;
    storage_now=p.storage_now;
    storage_all=p.storage_all;
}

void Books::Set_Book_Numb(QString &bnumb)
{
    if(bnumb.isEmpty())
        book_numb="#";
    else
        book_numb=bnumb;
}
void Books::Set_Book_Name(QString &bname)
{
    if(bname.isEmpty())
        book_name="#";
    else
        book_name=bname;
}
void Books::Set_Author_Numb(QString &anumb)
{
    if(anumb.isEmpty())
        author_numb="#";
    else
        author_numb=anumb;
}
void Books::Set_Author_Name(QString &aname)
{
    if(aname.isEmpty())
        author_name="#";
    else
        author_name=aname;
}
void Books::Set_Publisher_Numb(QString &pnumb)
{
    if(pnumb.isEmpty())
        publisher_numb="#";
    else
        publisher_numb=pnumb;
}
void Books::Set_Publisher_Name(QString &pname)
{
    if(pname.isEmpty())
        publisher_name="#";
    else
        publisher_name=pname;
}
void Books::Set_Storage_Now(int i)
{
    storage_now=i;
}
void Books::Set_Storage_All(int i)
{
    storage_all=i;
}

QString &Books::Get_Book_Numb()
{
    return book_numb;
}
QString &Books::Get_Book_Name()
{
    return book_name;
}
QString &Books::Get_Author_Numb()
{
    return author_numb;
}
QString &Books::Get_Author_Name()
{
    return author_name;
}
QString &Books::Get_Publisher_Numb()
{
    return publisher_numb;
}
QString &Books::Get_Publisher_Name()
{
    return publisher_name;
}
int Books::Get_Storage_now()
{
    return storage_now;
}
int Books::Get_Storage_all()
{
    return storage_all;
}
