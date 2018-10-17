#include <QWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QIntValidator>
#include <QApplication>
#include <QFont>
#include <QButtonGroup>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QList>
#include <QStringList>
#include <QMessageBox>
#include <QTabWidget>

#include "widget.h"
#include "users.h"
#include "pageuser.h"

PageUser::PageUser(QWidget *parent,QString &anumb):QWidget(parent)
{
    setWindowTitle("Users Page");
    resize(800,500);

    Readin_Books_Information();
    Readin_Users_Information();
    user_numb=anumb;

    Find_This_User();//==========确认这个用户是谁
    qDebug()<<user_numb;
    qDebug()<<this_user->Get_name();

    Initial_Layout();

    connect(tab0_flash,&QPushButton::clicked,this,&PageUser::Tab0_Flash_Clicked);
    connect(confirm,&QPushButton::clicked,this,&PageUser::Tab1_Confirm_Clicked);
    connect(tab2_show_book,&QPushButton::clicked,this,&PageUser::Tab2_Confirm1_Clicked);
    connect(tab2_confirm,&QPushButton::clicked,this,&PageUser::Tab2_Confirm2_Clicked);
    connect(tab3_confirm,&QPushButton::clicked,this,&PageUser::Tab3_Confirm_Clicked);
}

PageUser::~PageUser()
{
    Write_Users_In_File();
    Write_Books_In_File();
}

void PageUser::Initial_Layout()
{
    Initial_tab0();
    Initial_tab1();
    Initial_tab2();
    Initial_tab3();

    tab_widget=new QTabWidget(this);
    tab_widget->addTab(tab0,"Information");
    tab_widget->addTab(tab1,"Find");
    tab_widget->addTab(tab2,"Borrow");
    tab_widget->addTab(tab3,"Return");

    QVBoxLayout *vlayout=new QVBoxLayout;
    vlayout->addWidget(tab_widget);

    setLayout(vlayout);
}

void PageUser::Initial_tab0()
{
    tab0=new QWidget;

    tab0_showthing=new QTextEdit(tab0);
    tab0_showthing->setText("Your informations:");
    tab0_showthing->setReadOnly(true);
    tab0_showthing->moveCursor(QTextCursor::End);

    tab0_showthing->append("\n");
    tab0_showthing->insertPlainText(QString("ID:")+this_user->Get_id()+QString("\n"));
    tab0_showthing->insertPlainText(QString("Name:")+this_user->Get_name()+QString("\n"));
    tab0_showthing->insertPlainText(QString("Borrow Books Number:")+QString::number(this_user->Get_Books_Numb())+QString("\n"));

    if(this_user->Get_Books_Numb()>0)
    {
        for(int i=0;i<this_user->Get_Books_Numb();++i)
            tab0_showthing->insertPlainText(QString("Book Name:")+this_user->Get_Books(i)+QString("\n"));
    }

    tab0_flash=new QPushButton(tab0);
    tab0_flash->setText("flash");

    QVBoxLayout *layout= new QVBoxLayout;
    layout->addWidget(tab0_showthing);
    layout->addWidget(tab0_flash,0,Qt::AlignCenter);
    layout->setMargin(50);

    tab0->setLayout(layout);
}
void PageUser::Initial_tab1()
{
    tab1=new QWidget;

    QLabel *book_numb_tips,*book_name_tips;
    QLabel *author_numb_tips,*author_name_tips;
    QLabel *publisher_numb_tips,*publisher_name_tips;

    QRegExp regx("[a-zA-Z0-9]+$");

    //书号
    book_numb=new QLineEdit(tab1);
    book_numb->setPlaceholderText("Book ID");
    QValidator *vbook_numb= new QRegExpValidator(regx, book_numb);
    book_numb->setValidator(vbook_numb);
    book_numb->setMaxLength(3);

    book_numb_tips=new QLabel("Enter Book ID:",tab1);
    QHBoxLayout *book_numb_hlayout=new QHBoxLayout;
    book_numb_hlayout->addStretch();
    book_numb_hlayout->addWidget(book_numb_tips);
    book_numb_hlayout->addStretch();
    book_numb_hlayout->addWidget(book_numb);

    //书名
    book_name=new QLineEdit(tab1);
    book_name->setPlaceholderText("Book Name");

    book_name_tips=new QLabel("Enter Book Name:",tab1);
    QHBoxLayout *book_name_hlayout=new QHBoxLayout;
    book_name_hlayout->addStretch();
    book_name_hlayout->addWidget(book_name_tips);
    book_name_hlayout->addStretch();
    book_name_hlayout->addWidget(book_name);

    //作者号
    author_numb=new QLineEdit(tab1);
    author_numb->setPlaceholderText("Author Number");
    QValidator *vauthor_numb= new QRegExpValidator(regx, author_numb);
    author_numb->setValidator(vauthor_numb);
    author_numb->setMaxLength(3);

    author_numb_tips=new QLabel("Enter Author Numb:",tab1);
    QHBoxLayout *author_numb_hlayout=new QHBoxLayout;
    author_numb_hlayout->addStretch();
    author_numb_hlayout->addWidget(author_numb_tips);
    author_numb_hlayout->addStretch();
    author_numb_hlayout->addWidget(author_numb);

    //作者名
    author_name=new QLineEdit(tab1);
    author_name->setPlaceholderText("Author Name");

    author_name_tips=new QLabel("Enter Author Name:",tab1);
    QHBoxLayout *author_name_hlayout=new QHBoxLayout;
    author_name_hlayout->addStretch();
    author_name_hlayout->addWidget(author_name_tips);
    author_name_hlayout->addStretch();
    author_name_hlayout->addWidget(author_name);

    //出版社号
    publisher_numb=new QLineEdit(tab1);
    publisher_numb->setPlaceholderText("Publisher Number");
    QValidator *vpublisher_numb= new QRegExpValidator(regx, publisher_numb);
    publisher_numb->setValidator(vpublisher_numb);
    publisher_numb->setMaxLength(3);

    publisher_numb_tips=new QLabel("Enter Publisher Numb:",tab1);
    QHBoxLayout *publisher_numb_hlayout=new QHBoxLayout;
    publisher_numb_hlayout->addStretch();
    publisher_numb_hlayout->addWidget(publisher_numb_tips);
    publisher_numb_hlayout->addStretch();
    publisher_numb_hlayout->addWidget(publisher_numb);

    //出版社名
    publisher_name=new QLineEdit(tab1);
    publisher_name->setPlaceholderText("Publisher Name");

    publisher_name_tips=new QLabel("Enter Publisher Name:",tab1);
    QHBoxLayout *publisher_name_hlayout=new QHBoxLayout;
    publisher_name_hlayout->addStretch();
    publisher_name_hlayout->addWidget(publisher_name_tips);
    publisher_name_hlayout->addStretch();
    publisher_name_hlayout->addWidget(publisher_name);

    //按钮
    confirm=new QPushButton(tab1);
    confirm->setText("Inquiry");

    QVBoxLayout *tab1_vlayout1=new QVBoxLayout;

    tab1_vlayout1->addLayout(book_numb_hlayout);
    tab1_vlayout1->addLayout(book_name_hlayout);
    tab1_vlayout1->addLayout(author_numb_hlayout);
    tab1_vlayout1->addLayout(author_name_hlayout);
    tab1_vlayout1->addLayout(publisher_numb_hlayout);
    tab1_vlayout1->addLayout(publisher_name_hlayout);
    tab1_vlayout1->addWidget(confirm);

    //输出框
    show_something=new QTextEdit(tab1);
    show_something->setText("Book informations:\n");
    show_something->setReadOnly(true);

    QHBoxLayout *tab1_hlayout=new QHBoxLayout;
    tab1_hlayout->addLayout(tab1_vlayout1);
    tab1_hlayout->addWidget(show_something);

    tab1->setLayout(tab1_hlayout);
}
void PageUser::Initial_tab2()
{
    tab2=new QWidget;

    QRegExp regx("[a-zA-Z0-9]+$");

    QLabel tab2_numb_tip("Enter the book ID:",tab2);

    tab2_numb=new QLineEdit(tab2);
    QValidator *vnumb=new QRegExpValidator(regx, tab2_numb);
    tab2_numb->setValidator(vnumb);
    tab2_numb->setPlaceholderText("book ID");
    tab2_numb->setMaxLength(3);

    QHBoxLayout *numb_hlayout=new QHBoxLayout;
    numb_hlayout->addWidget(&tab2_numb_tip);
    numb_hlayout->addWidget(tab2_numb);

    tab2_show_book=new QPushButton(tab2);
    tab2_show_book->setText("Show this book information");

    tab2_confirm=new QPushButton(tab2);
    tab2_confirm->setText("Borrow this book");

    QVBoxLayout *left_vlayout=new QVBoxLayout;
    left_vlayout->addStretch();
    left_vlayout->addLayout(numb_hlayout);
    left_vlayout->addStretch();
    left_vlayout->addWidget(tab2_show_book);
    left_vlayout->addWidget(tab2_confirm);

    tab2_show_something=new QTextEdit(tab2);
    tab2_show_something->setText("Books information:\n");
    tab2_show_something->setReadOnly(true);

    QHBoxLayout *hlayout=new QHBoxLayout;
    hlayout->addLayout(left_vlayout);
    hlayout->addWidget(tab2_show_something);

    tab2->setLayout(hlayout);
}
void PageUser::Initial_tab3()
{
    tab3=new QWidget;

    QRegExp regx("[a-zA-Z0-9]+$");

    QLabel tab3_numb_tip("Enter the book ID:",tab3);

    tab3_numb=new QLineEdit(tab3);
    QValidator *vnumb=new QRegExpValidator(regx, tab3_numb);
    tab3_numb->setValidator(vnumb);
    tab3_numb->setPlaceholderText("book ID");
    tab3_numb->setMaxLength(3);

    QHBoxLayout *numb_hlayout=new QHBoxLayout;
    numb_hlayout->addWidget(&tab3_numb_tip);
    numb_hlayout->addWidget(tab3_numb);

    tab3_confirm=new QPushButton(tab3);
    tab3_confirm->setText("Return this book");

    QVBoxLayout *left_vlayout=new QVBoxLayout;
    left_vlayout->addStretch();
    left_vlayout->addLayout(numb_hlayout);
    left_vlayout->addStretch();
    left_vlayout->addWidget(tab3_confirm);

    tab3_show_something=new QTextEdit(tab3);
    tab3_show_something->setText("Books information:\n");
    tab3_show_something->setReadOnly(true);

    QHBoxLayout *hlayout=new QHBoxLayout;
    hlayout->addLayout(left_vlayout);
    hlayout->addWidget(tab3_show_something);

    tab3->setLayout(hlayout);
}

void PageUser::Readin_Books_Information()
{
    QFile file_book(":/txt/book");
    if(!file_book.open(QFile::ReadOnly|QFile::Text))
    {
        qDebug() << "Could not open file for Reading";
        return;
    }
    QTextStream in(&file_book);
    QString temp_line_string;
    while(!in.atEnd())
    {
        temp_line_string=in.readLine();
        Books *new_book=new Books;
        new_book->Set_Book_Numb(temp_line_string.section(' ',0,0));
        new_book->Set_Book_Name(temp_line_string.section(' ',1,1));
        new_book->Set_Author_Numb(temp_line_string.section(' ',2,2));
        new_book->Set_Author_Name(temp_line_string.section(' ',3,3));
        new_book->Set_Publisher_Numb(temp_line_string.section(' ',4,4));
        new_book->Set_Publisher_Name(temp_line_string.section(' ',5,5));
        new_book->Set_Storage_Now(temp_line_string.section(' ',6,6).toInt());
        new_book->Set_Storage_All(temp_line_string.section(' ',7,7).toInt());

        books.append(*new_book);
    }
    file_book.close();
}
void PageUser::Readin_Users_Information()
{
    QFile file_user_id(":/txt/id");
    if(!file_user_id.open(QFile::ReadOnly|QFile::Text))
    {
        qDebug() << "Could not open file for Reading";
        return;
    }
    QTextStream in(&file_user_id);
    QString temp_line_string;
    while(!in.atEnd())
    {
        temp_line_string=in.readLine();
        Users *new_user=new Users;

        new_user->Set_name(temp_line_string.section(' ',0,0));
        new_user->Set_id(temp_line_string.section(' ',1,1));
        new_user->Set_password(temp_line_string.section(' ',2,2));
        if(temp_line_string.section(' ',3,3)==QString("administer"))
            new_user->Set_administer(true);
        else
            new_user->Set_administer(false);
        new_user->Set_Books_Numb(temp_line_string.section(' ',4,4).toInt());

        for(int i=1;i<=new_user->Get_Books_Numb();++i)
        {
            new_user->Add_Books(temp_line_string.section(' ',i+4,i+4));
        }

        users.append(*new_user);
    }

    file_user_id.close();
}

void PageUser::Write_Books_In_File()
{
    QFile w("H:/QT creator/Library/books.txt");
    if(!w.open(QFile::WriteOnly|QFile::Text))
    {
        qDebug()<<"Could not open file for Reading";
        return  ;
    }
    QTextStream in(&w);
    QList<Books>::iterator i;
    for(i=books.begin();i!=books.end();++i)
    {
        if(i->Get_Book_Numb()=='#')
            continue;
        in<<i->Get_Book_Numb()<<' '<<i->Get_Book_Name()<<' '
         <<i->Get_Author_Numb()<<' '<<i->Get_Author_Name()<<' '
        <<i->Get_Publisher_Numb()<<' '<<i->Get_Publisher_Name()<<' '
        <<i->Get_Storage_now()<<' '<<i->Get_Storage_all()<<'\n';
    }
    w.close();
}
void PageUser::Write_Users_In_File()
{
    QFile w("H:/QT creator/Library/user_id.txt");
    if(!w.open(QFile::WriteOnly|QFile::Text))
    {
        qDebug()<<"Could not open file for Reading";
        return  ;
    }

    QTextStream in(&w);
    QList<Users>::iterator i;
    for(i=users.begin();i!=users.end();++i)
    {
        qDebug()<<"exe";
        in<<i->Get_name()<<' '<<i->Get_id()<<' '<<i->Get_password()<<' ';
        if(i->is_administrable())
            in<<"administer"<<' ';
        else
            in<<"user"<<' ';
        in<<i->Get_Books_Numb()<<' ';
        if(i->Get_Books_Numb()==0)
            in<<'\n';
        else
        {
            for(int index=0;index<i->Get_Books_Numb();++index)
            {
                in<<i->Get_Books(index);
                if(i->Get_Books_Numb()-1==index)
                    in<<'\n';
                else
                    in<<' ';
            }
        }
    }
    w.close();
}

void PageUser::Tab0_Flash_Clicked()
{
    tab0_showthing->append("\n");
    tab0_showthing->insertPlainText(QString("ID:")+this_user->Get_id()+QString("\n"));
    tab0_showthing->insertPlainText(QString("Name:")+this_user->Get_name()+QString("\n"));
    tab0_showthing->insertPlainText(QString("Borrow Books Number:")+QString::number(this_user->Get_Books_Numb())+QString("\n"));

    if(this_user->Get_Books_Numb()>0)
    {
        for(int i=0;i<this_user->Get_Books_Numb();++i)
        {
            tab0_showthing->insertPlainText(QString("Book Numb:")+this_user->Get_Books(i)+QString("\n"));
        }

    }
}

void PageUser::Tab1_Confirm_Clicked()
{
    QString bnumb=book_numb->text(),
            bname=book_name->text(),
            anumb=author_numb->text(),
            aname=author_name->text(),
            pnumb=publisher_numb->text(),
            pname=publisher_name->text();

    if(bnumb.isEmpty()&&bname.isEmpty()&&anumb.isEmpty()
            &&aname.isEmpty()&&pnumb.isEmpty()&&pname.isEmpty())
    {
        show_something->append("\n");
        show_something->moveCursor(QTextCursor::End);
        show_something->insertPlainText("You must write something ^.^");
        return;
    }

    Books *new_book=new Books;
    new_book->Set_Book_Numb(bnumb);
    new_book->Set_Book_Name(bname);
    new_book->Set_Author_Numb(anumb);
    new_book->Set_Author_Name(aname);
    new_book->Set_Publisher_Numb(pnumb);
    new_book->Set_Publisher_Name(pname);

    QList<Books>::iterator i;
    QList<Books> its;

    for(i=books.begin();i!=books.end();++i)
    {
        bool flag=true;
        if(!i->Get_Book_Numb().contains(new_book->Get_Book_Numb())
                &&new_book->Get_Book_Numb()!=QString("#"))
            flag=false;
        if(!i->Get_Book_Name().contains(new_book->Get_Book_Name())
                &&new_book->Get_Book_Name()!=QString("#"))
            flag=false;
        if(!i->Get_Author_Numb().contains(new_book->Get_Author_Numb())
                &&new_book->Get_Author_Numb()!=QString("#"))
            flag=false;
        if(!i->Get_Author_Name().contains(new_book->Get_Author_Name())
                &&new_book->Get_Author_Name()!=QString("#"))
            flag=false;
        if(!i->Get_Publisher_Numb().contains(new_book->Get_Publisher_Numb())
                &&new_book->Get_Publisher_Numb()!=QString("#"))
            flag=false;
        if(!i->Get_Publisher_Name().contains(new_book->Get_Publisher_Name())
                &&new_book->Get_Publisher_Name()!=QString("#"))
            flag=false;
        if(flag)
            its.append(*i);
    }

    if(!its.empty())
    {
        QList<Books>::iterator j;
        for(j=its.begin();j!=its.end();++j)
        {
            show_something->append("\n");
            show_something->moveCursor(QTextCursor::End);
            show_something->insertPlainText("Book No.");
            show_something->insertPlainText(j->Get_Book_Numb()+QString(" ")+j->Get_Book_Name());
            show_something->append("Author:");
            show_something->insertPlainText(j->Get_Author_Numb()+QString(' ')+j->Get_Author_Name());
            show_something->append("Publisher:");
            show_something->insertPlainText(j->Get_Publisher_Numb()+QString(' ')+j->Get_Publisher_Name());
            show_something->append("Can borrow:");
            show_something->insertPlainText(QString::number(j->Get_Storage_now()));
            show_something->append("All storage:");
            show_something->insertPlainText(QString::number(j->Get_Storage_all()));
        }
    }
    else
    {
        show_something->append("\n");
        show_something->moveCursor(QTextCursor::End);
        show_something->insertPlainText(QString("This book is not existing -^-"));
    }
}

void PageUser::Tab2_Confirm1_Clicked()
{
    QString bnumb=tab2_numb->text();

    QList<Books>::iterator i;
    bool flag=false;
    for(i=books.begin();i!=books.end();++i)
    {
        if(i->Get_Book_Numb()==bnumb)
        {
            flag=true;
            break ;
        }
    }
    if(flag)
    {
        tab2_show_something->append("\n");
        tab2_show_something->moveCursor(QTextCursor::End);
        tab2_show_something->insertPlainText("Book No.");
        tab2_show_something->insertPlainText(i->Get_Book_Numb()+QString(" ")+i->Get_Book_Name());
        tab2_show_something->append("Author:");
        tab2_show_something->insertPlainText(i->Get_Author_Numb()+QString(' ')+i->Get_Author_Name());
        tab2_show_something->append("Publisher:");
        tab2_show_something->insertPlainText(i->Get_Publisher_Numb()+QString(' ')+i->Get_Publisher_Name());
        tab2_show_something->append("Can borrow:");
        tab2_show_something->insertPlainText(QString::number(i->Get_Storage_now()));
        tab2_show_something->append("All storage:");
        tab2_show_something->insertPlainText(QString::number(i->Get_Storage_all()));
    }
    else
    {
        tab2_show_something->append("\n");
        tab2_show_something->moveCursor(QTextCursor::End);
        tab2_show_something->insertPlainText("This book is not existing -^-");
    }
}
void PageUser::Tab2_Confirm2_Clicked()
{
    QString bnumb=tab2_numb->text();

    QList<Books>::iterator i;
    bool flag=false;
    for(i=books.begin();i!=books.end();++i)
    {
        if(i->Get_Book_Numb()==bnumb)
        {
            flag=true;
            break ;
        }
    }
    if(flag)
    {
        if(i->Get_Storage_now()>0)//===============借书成功
        {
            i->Set_Storage_Now(i->Get_Storage_now()-1);

            tab2_show_something->append("\n");
            tab2_show_something->moveCursor(QTextCursor::End);
            tab2_show_something->insertPlainText("Borrow successfully\n");
            tab2_show_something->insertPlainText("Book No.");
            tab2_show_something->insertPlainText(i->Get_Book_Numb()+QString(" ")+i->Get_Book_Name());
            tab2_show_something->append("Author:");
            tab2_show_something->insertPlainText(i->Get_Author_Numb()+QString(' ')+i->Get_Author_Name());
            tab2_show_something->append("Publisher:");
            tab2_show_something->insertPlainText(i->Get_Publisher_Numb()+QString(' ')+i->Get_Publisher_Name());
            tab2_show_something->append("Can borrow:");
            tab2_show_something->insertPlainText(QString::number(i->Get_Storage_now()+1)+"->"+QString::number(i->Get_Storage_now()));
            tab2_show_something->append("All storage:");
            tab2_show_something->insertPlainText(QString::number(i->Get_Storage_all()));

            this_user->Set_Books_Numb(this_user->Get_Books_Numb()+1);
            this_user->Add_Books(i->Get_Book_Numb());
        }
        else
        {
            tab2_show_something->append("\n");
            tab2_show_something->moveCursor(QTextCursor::End);
            tab2_show_something->insertPlainText("Borrow unsuccessfully\n");
            tab2_show_something->insertPlainText("This book is out of stock -^-\n");
            tab2_show_something->insertPlainText("Book No.");
            tab2_show_something->insertPlainText(i->Get_Book_Numb()+QString(" ")+i->Get_Book_Name());
            tab2_show_something->append("Author:");
            tab2_show_something->insertPlainText(i->Get_Author_Numb()+QString(' ')+i->Get_Author_Name());
            tab2_show_something->append("Publisher:");
            tab2_show_something->insertPlainText(i->Get_Publisher_Numb()+QString(' ')+i->Get_Publisher_Name());
            tab2_show_something->append("Can borrow:");
            tab2_show_something->insertPlainText(QString::number(i->Get_Storage_now()));
            tab2_show_something->append("All storage:");
            tab2_show_something->insertPlainText(QString::number(i->Get_Storage_all()));
        }
    }
    else
    {
        tab2_show_something->append("\n");
        tab2_show_something->moveCursor(QTextCursor::End);
        tab2_show_something->insertPlainText("Borrow unsuccessfully\n");
        tab2_show_something->insertPlainText("This book is not existing -^-");
    }
}

void PageUser::Tab3_Confirm_Clicked()
{
    QString bnumb=tab3_numb->text();

    QList<Books>::iterator i;
    bool flag=false;
    for(i=books.begin();i!=books.end();++i)
    {
        if(i->Get_Book_Numb()==bnumb)
        {
            flag=true;
            break ;
        }
    }
    if(flag)//这本书在书库中存在
    {
        bool flag2=false;
        qDebug()<<this_user->Get_Books_Numb()<<bnumb;
        for(int i=0;i<this_user->Get_Books_Numb();++i)
        {
            if(this_user->Get_Books(i)==bnumb)
            {
                flag2=true;
                break;
            }
            qDebug()<<this_user->Get_Books(i);
        }
        if(flag2)//拥有这本书
        {
            tab3_show_something->append("\n");
            tab3_show_something->moveCursor(QTextCursor::End);
            tab3_show_something->insertPlainText("Return successfully\n");
            tab3_show_something->insertPlainText("Book No.");
            tab3_show_something->insertPlainText(i->Get_Book_Numb()+QString(" ")+i->Get_Book_Name());
            tab3_show_something->append("Author:");
            tab3_show_something->insertPlainText(i->Get_Author_Numb()+QString(' ')+i->Get_Author_Name());
            tab3_show_something->append("Publisher:");
            tab3_show_something->insertPlainText(i->Get_Publisher_Numb()+QString(' ')+i->Get_Publisher_Name());
            tab3_show_something->append("Can borrow:");
            tab3_show_something->insertPlainText(QString::number(i->Get_Storage_now())+"->"+QString::number(i->Get_Storage_now()+1));
            tab3_show_something->append("All storage:");
            tab3_show_something->insertPlainText(QString::number(i->Get_Storage_all()));

            i->Set_Storage_Now(i->Get_Storage_now()+1);
            this_user->Set_Books_Numb(this_user->Get_Books_Numb()-1);
            this_user->Erase_Books(bnumb);
        }
        else
        {
            tab3_show_something->append("\n");
            tab3_show_something->moveCursor(QTextCursor::End);
            tab3_show_something->insertPlainText("Return unsuccessfully\n");
            tab3_show_something->insertPlainText("You have not this book = =");
        }

    }
    else//此书在书库中不存在
    {
        tab3_show_something->append("\n");
        tab3_show_something->moveCursor(QTextCursor::End);
        tab3_show_something->insertPlainText("Return unsuccessfully\n");
        tab3_show_something->insertPlainText("This book is not existing -^-");
    }
}

void PageUser::Set_User(QString &puser_numb)
{
    user_numb=puser_numb;
}
void PageUser::Find_This_User()
{
    QList<Users>::iterator i;
    for(i=users.begin();i!=users.end();++i)
    {
        if(i->Get_id()==user_numb)
        {
            this_user=i;
            break;
        }
    }
}
