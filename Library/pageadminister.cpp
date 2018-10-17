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
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QList>
#include <QMessageBox>
#include <QTabWidget>
#include <QTextEdit>

#include "widget.h"
#include "users.h"
#include "pageadminister.h"

PageAdminister::PageAdminister(QWidget *parent):QWidget(parent)
{
    setWindowTitle("Administer Page");
    resize(800,500);
    Initial_Layout();
    Readin_Books_Information();

    connect(confirm,&QPushButton::clicked,this,&PageAdminister::Confirm_Clicked);
    connect(tab2_confirm,&QPushButton::clicked,this,&PageAdminister::Tab2_Clicked);
}

PageAdminister::~PageAdminister()
{
    Write_In_File();
}

void PageAdminister::Initial_Layout()
{
    Initial_tab1();
    Initial_tab2();
    tab_widget=new QTabWidget(this);
    tab_widget->addTab(tab1,"Add books");
    tab_widget->addTab(tab2,"Remove books");

    QVBoxLayout *vLayout=new QVBoxLayout;
    vLayout->addWidget(tab_widget);

    setLayout(vLayout);
}

void PageAdminister::Initial_tab1()
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

    QVBoxLayout *tab1_vlayout1=new QVBoxLayout;

    tab1_vlayout1->addLayout(book_numb_hlayout);
    tab1_vlayout1->addLayout(book_name_hlayout);
    tab1_vlayout1->addLayout(author_numb_hlayout);
    tab1_vlayout1->addLayout(author_name_hlayout);
    tab1_vlayout1->addLayout(publisher_numb_hlayout);
    tab1_vlayout1->addLayout(publisher_name_hlayout);

    //输出框
    show_something=new QTextEdit(tab1);
    show_something->setText("Adding book informations:\n");
    show_something->setReadOnly(true);


    //提示框与输入数量策应
    QLabel *book_quantity_tips=new QLabel(tab1);
    book_quantity_tips->setText("Enter the quantity of this book");

    //数量
    book_quantity=new QLineEdit(tab1);
    book_quantity->setPlaceholderText("How many");
    book_quantity->setValidator(new QIntValidator(book_quantity));

    //按钮
    confirm=new QPushButton(tab1);
    confirm->setText("Add this book");

    QVBoxLayout *tab1_vlayout2=new QVBoxLayout;

    tab1_vlayout2->addStretch();
    tab1_vlayout2->addWidget(show_something);
    tab1_vlayout2->addStretch();
    tab1_vlayout2->addWidget(book_quantity_tips,0,Qt::AlignCenter);
    tab1_vlayout2->addWidget(book_quantity,0,Qt::AlignCenter);
    tab1_vlayout2->addStretch();
    tab1_vlayout2->addWidget(confirm,0,Qt::AlignCenter);
    tab1_vlayout2->addStretch();

    QHBoxLayout *tab1_hlayout=new QHBoxLayout;
    tab1_hlayout->addLayout(tab1_vlayout1);
    tab1_hlayout->addLayout(tab1_vlayout2);

    tab1->setLayout(tab1_hlayout);
}

void PageAdminister::Initial_tab2()
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

    tab2_confirm=new QPushButton(tab2);
    tab2_confirm->setText("Delete it");

    QVBoxLayout *left_vlayout=new QVBoxLayout;
    left_vlayout->addLayout(numb_hlayout);
    left_vlayout->addWidget(tab2_confirm);

    tab2_show_something=new QTextEdit(tab2);
    tab2_show_something->setText("Deleting books information:\n");
    tab2_show_something->setReadOnly(true);

    QHBoxLayout *hlayout=new QHBoxLayout;
    hlayout->addLayout(left_vlayout);
    hlayout->addWidget(tab2_show_something);

    tab2->setLayout(hlayout);
}

void PageAdminister::Readin_Books_Information()
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

void PageAdminister::Confirm_Clicked()
{
    QString bnumb=book_numb->text(),
            bname=book_name->text(),
            anumb=author_numb->text(),
            aname=author_name->text(),
            pnumb=publisher_numb->text(),
            pname=publisher_name->text();
    int s_all=book_quantity->text().toInt();


    if(bnumb.isEmpty())
    {
        show_something->append("\n");
        show_something->moveCursor(QTextCursor::End);
        show_something->insertPlainText("There has no book ^.^");
        return;
    }
    //===========如果存在这本书，库存加上数量
    QList<Books>::iterator i;
    if(Is_Exist(bnumb,i))
    {
        i->Set_Storage_All(s_all+i->Get_Storage_all());
        i->Set_Storage_Now(s_all+i->Get_Storage_now());

        //=======显示
        show_something->append("\n");
        show_something->moveCursor(QTextCursor::End);
        show_something->insertPlainText(i->Get_Book_Numb());
        show_something->insertPlainText(QString(" is exsiting and the storage has been resized "));
        show_something->insertPlainText(QString::number(i->Get_Storage_now())+QString("/")+QString::number(i->Get_Storage_all()));
    }
    else//===============若不存在，新建
    {
         Books *new_book=new Books;
         new_book->Set_Book_Numb(bnumb);
         new_book->Set_Book_Name(bname);
         new_book->Set_Author_Numb(anumb);
         new_book->Set_Author_Name(aname);
         new_book->Set_Publisher_Numb(pnumb);
         new_book->Set_Publisher_Name(pname);
         new_book->Set_Storage_Now(s_all);
         new_book->Set_Storage_All(s_all);

         books.append(*new_book);

         //======显示
         show_something->append("\n");
         show_something->moveCursor(QTextCursor::End);
         show_something->insertPlainText(new_book->Get_Book_Numb());
         show_something->insertPlainText(QString(" has been created "));
         show_something->insertPlainText(QString::number(new_book->Get_Storage_now())+QString("/")+QString::number(new_book->Get_Storage_all()));
    }

}

bool PageAdminister::Is_Exist(QString &bnumb,QList<Books>::iterator &i)
{
    for(i=books.begin();i!=books.end();++i)
    {
        if(i->Get_Book_Numb()==bnumb)
        {
            return true;
        }
    }
    return false;
}

void PageAdminister::Write_In_File()
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

void PageAdminister::Tab2_Clicked()
{
    QString bnumb=tab2_numb->text();

    if(bnumb.isEmpty())
    {
        tab2_show_something->append(" ");
        tab2_show_something->moveCursor(QTextCursor::End);
        tab2_show_something->insertPlainText("There has no book ^.^");
        return;
    }

    QList<Books>::iterator i;
    if(Is_Exist(bnumb,i))//这本书存在，删除
    {
        tab2_show_something->append("\n");
        tab2_show_something->moveCursor(QTextCursor::End);
        tab2_show_something->insertPlainText("Book No.");
        tab2_show_something->insertPlainText(i->Get_Book_Numb()+QString(' ')+i->Get_Book_Name());
        tab2_show_something->append("Author:");
        tab2_show_something->insertPlainText(i->Get_Author_Numb()+QString(' ')+i->Get_Author_Name());
        tab2_show_something->append("Publisher:");
        tab2_show_something->insertPlainText(i->Get_Publisher_Numb()+QString(' ')+i->Get_Publisher_Name());
        tab2_show_something->append("has already erased X.X");

        books.erase(i);
    }
    else//不存在
    {
        tab2_show_something->append("\n");
        tab2_show_something->moveCursor(QTextCursor::End);
        tab2_show_something->insertPlainText("This book is not existing in your library ^.^");
    }
}
