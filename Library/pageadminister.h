#ifndef PAGEADMINISTER_H
#define PAGEADMINISTER_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QTabWidget>
#include <QList>
#include <QPushButton>
#include <QTextEdit>

#include "pageadminister.h"
#include "books.h"

class PageAdminister:public QWidget
{
    Q_OBJECT

public:
    explicit PageAdminister(QWidget *parent = 0);
    ~PageAdminister();

private://控件
    QTabWidget *tab_widget;

    //==========tab1的控件
    QWidget *tab1;
    QLineEdit *book_numb,*book_name;
    QLineEdit *author_name,*author_numb;
    QLineEdit *publisher_name,*publisher_numb;
    QLineEdit *book_quantity;
    QPushButton *confirm;
    QTextEdit *show_something;

    //==========tab2的控件
    QWidget *tab2;
    QLineEdit *tab2_numb;
    QPushButton *tab2_confirm;
    QTextEdit *tab2_show_something;

public://===================初始化布局
    void Initial_Layout();//初始化大布局

    void Initial_tab1();//初始化tab1采编入库布局
    void Initial_tab2();//初始化tab2删除书目布局

private://===================自定义类
    QList<Books> books;

public://===================自定义类函数
    void Readin_Books_Information();
    bool Is_Exist(QString &bnumb,QList<Books>::iterator &i);
    void Write_In_File();

    //====tab1
    void Confirm_Clicked();

    //====tab2
    void Tab2_Clicked();

};

#endif // PAGEADMINISTER_H
