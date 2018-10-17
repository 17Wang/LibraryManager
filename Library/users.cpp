#include <QLabel>
#include <QStringList>

#include "users.h"

Users::Users(QString &name,QString &id,QString &password,bool administer,int book_numb)
{
    user_name=name;
    user_id=id;
    user_password=password;
    administrable=administer;
    borrow_books_numb=book_numb;
}

Users::Users(const Users &p)
{
    user_name=p.user_name;
    user_id=p.user_id;
    user_password=p.user_password;
    administrable=p.administrable;
    borrow_books_numb=p.borrow_books_numb;
    borrow_books=p.borrow_books;
}

void Users::Set_name(QString &name)
{
    user_name=name;
}
void Users::Set_id(QString &id)
{
    user_id=id;
}
void Users::Set_password(QString &password)
{
    user_password=password;
}
void Users::Set_administer(bool administer)
{
    administrable=administer;
}
void Users::Set_Books_Numb(int numb)
{
    borrow_books_numb=numb;
}
void Users::Add_Books(const QString& book_id)
{
    borrow_books.append(book_id);
}
void Users::Erase_Books(const QString &bnumb)
{
    QStringList::iterator it;
    for(it=borrow_books.begin();it!=borrow_books.end();++it)
    {
        if(*it==bnumb)
        {
            borrow_books.erase(it);
            return;
        }
    }
    borrow_books_numb--;
}

QString &Users::Get_name()
{
    return user_name;
}
QString &Users::Get_id()
{
    return user_id;
}
QString &Users::Get_password()
{
    return user_password;
}
bool Users::is_administrable()
{
    return administrable;
}
int Users::Get_Books_Numb()
{
    return borrow_books_numb;
}
QString Users::Get_Books(int i)
{
    return borrow_books.at(i);
}

