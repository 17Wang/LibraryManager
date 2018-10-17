#ifndef PAGEUSER_H
#define PAGEUSER_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QTabWidget>
#include <QList>
#include <QPushButton>
#include <QTextEdit>

#include "books.h"
#include "users.h"

class PageUser:public QWidget
{
    Q_OBJECT

public:
    explicit PageUser(QWidget *parent = 0,QString &anumb=QString("0"));
    ~PageUser();

private://==========控件
    QTabWidget *tab_widget;

    //=========tab0的控件，显示
    QWidget *tab0;
    QTextEdit *tab0_showthing;
    QPushButton *tab0_flash;

    //==========tab1的控件，查找
    QWidget *tab1;
    QLineEdit *book_numb,*book_name;
    QLineEdit *author_name,*author_numb;
    QLineEdit *publisher_name,*publisher_numb;
    QPushButton *confirm;
    QTextEdit *show_something;

    //==========tab2的控件，借阅
    QWidget *tab2;
    QLineEdit *tab2_numb;
    QPushButton *tab2_show_book;
    QPushButton *tab2_confirm;
    QTextEdit *tab2_show_something;

    //==========tab3的控件，归还
    QWidget *tab3;
    QLineEdit *tab3_numb;
    QPushButton *tab3_confirm;
    QTextEdit *tab3_show_something;

public://============控件初始化
    void Initial_Layout();//初始化大布局

    void Initial_tab0();//初始化tab0用户信息查看
    void Tab0_Flash_Clicked();//tab0的按钮操作

    void Initial_tab1();//初始化tab1查询布局
    void Tab1_Confirm_Clicked();//tab1的按钮操作

    void Initial_tab2();//初始化tab2借阅布局
    void Tab2_Confirm1_Clicked();//tab2的查看按钮操作
    void Tab2_Confirm2_Clicked();//tab2的借阅按钮操作,还需要改写用户的信息。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。

    void Initial_tab3();//初始化tab3归还布局
    void Tab3_Confirm_Clicked();

private://===========读取登录页面的用户信息，改写用户信息
    QList<Users> users;
    QString user_numb;
    QList<Users>::iterator this_user;

public://============对Users类的操作
    void Readin_Users_Information();
    void Write_Users_In_File();
    void Set_User(QString &puser_numb);//通过用户号来确定
    void Find_This_User();

private://===========读取书籍的信息
    QList<Books> books;

public://=============对Books类的操作
    void Readin_Books_Information();
    bool Is_Exist(QString &bnumb,QList<Books>::iterator &i);
    void Write_Books_In_File();

};

#endif // PAGEUSER_H
