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
#include <QMessageBox>
#include <QTabWidget>

#include "widget.h"
#include "ui_widget.h"
#include "users.h"
#include "pageadminister.h"
#include "pageuser.h"


Widget::Widget(QWidget *parent):QWidget(parent),ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Library Manager");

    main_page_administer=NULL;
    main_page_user=NULL;

    Initial_Layout();
    Readin_Users_Informations();

    //控制台显示帐密
    Show_QList_Users();

    connect(Login,&QPushButton::clicked,this,&Widget::Login_Button);
}

Widget::~Widget()
{
    if(main_page_administer!=NULL)
        main_page_administer->~PageAdminister();
    if(main_page_user!=NULL)
        main_page_user->~PageUser();
    delete ui;
}

void Widget::Initial_Layout()
{
    //======title
    QFont font("Microsoft YaHei", 20, QFont::Light);
    title=new QLabel(this);
    title->setFont(font);
    title->setText("Login Interface");

    //======user_id
    user_id=new QLineEdit(this);
    user_id->setPlaceholderText("Enter ID");
    user_id->setEchoMode(QLineEdit::Normal);
    user_id->setAlignment(Qt::AlignLeft);
    user_id->setMaxLength(14);//24320162202918 十四位
    QRegExp regx("[0-9]+$");
    QValidator *validator1 = new QRegExpValidator(regx, user_id );
    user_id->setValidator( validator1 );

    //======pass_word
    pass_word=new QLineEdit(this);
    pass_word->setPlaceholderText("Enter Password");
    pass_word->setEchoMode(QLineEdit::Password);
    pass_word->setAlignment(Qt::AlignLeft);
    pass_word->setMaxLength(6);//最多六位
    QValidator *validator2 = new QRegExpValidator(regx, pass_word );
    pass_word->setValidator( validator2 );

    //======Login(push button)
    Login=new QPushButton(this);
    Login->setText("Login");

    //======administer and user
    administer=new QRadioButton(this);
    administer->setText("administer");
    administer->setToolTip("if you are administer");

    user=new QRadioButton(this);
    user->setText("user");
    user->setToolTip("if you are user");
    user->setChecked(true);

    QVBoxLayout *Choose=new QVBoxLayout;
    Choose->addWidget(user);
    Choose->addWidget(administer);

    QButtonGroup *pChoose=new QButtonGroup;
    pChoose->addButton(administer);
    pChoose->addButton(user);

    //======Layout
    QVBoxLayout *EditLayout=new QVBoxLayout;
    EditLayout->addWidget(title,0,Qt::AlignCenter);
    EditLayout->addStretch();
    EditLayout->addWidget(user_id);
    EditLayout->addWidget(pass_word);
    EditLayout->addLayout(Choose);
    EditLayout->addWidget(Login);
    EditLayout->addStretch();

    EditLayout->setAlignment(Choose,Qt::AlignCenter);
    EditLayout->setContentsMargins(50,30,50,30);

    setLayout(EditLayout);
}

void Widget::Login_Button()
{
    QString id=user_id->text();
    QString pword=pass_word->text();

    bool find_flag=false;

    QList<Users>::iterator i;
    for(i=users.begin();i!=users.end();++i)
    {
        if(i->Get_id()==id&&i->Get_password()==pword)
        {
            find_flag=true;
            break;
        }
    }
    if(find_flag)
    {
        //跳转至主界面
       if(user->isChecked())
       {
           main_page_user=new PageUser(0,id);
           if(close())
                main_page_user->show();
       }
       else if(i->is_administrable())
       {
           main_page_administer=new PageAdminister;
           if(close())
                main_page_administer->show();
       }
       else
       {
           //跳出身份错误警告Dialog
           QMessageBox warn1(QMessageBox::Warning,"Information","You are not the administer",QMessageBox::Yes,NULL);
           warn1.setButtonText(QMessageBox::Yes,"OK");
           warn1.exec();
       }
    }
    else
    {
        //跳出输入错误警告Dialog
        QMessageBox warn(QMessageBox::Warning,"Information","Please check your id and password",QMessageBox::Yes,NULL);
        warn.setButtonText(QMessageBox::Yes,"OK");
        warn.exec();
    }
}

void Widget::Readin_Users_Informations()
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
        if(!temp_line_string.section(' ',0,0).isEmpty())
            new_user->Set_name(temp_line_string.section(' ',0,0));
        if(!temp_line_string.section(' ',1,1).isEmpty())
            new_user->Set_id(temp_line_string.section(' ',1,1));
        if(!temp_line_string.section(' ',2,2).isEmpty())
            new_user->Set_password(temp_line_string.section(' ',2,2));
        if(!temp_line_string.section(' ',3,3).isEmpty())
            if(temp_line_string.section(' ',3,3)==QString("administer"))
                new_user->Set_administer(true);
            else
                new_user->Set_administer(false);
        if(!temp_line_string.section(' ',4,4).isEmpty())
            new_user->Set_Books_Numb(temp_line_string.section(' ',4,4).toInt());
        for(int i=1;i<=new_user->Get_Books_Numb();++i)
        {
            new_user->Add_Books(temp_line_string.section(' ',i+4,i+4));
        }
        users.append(*new_user);
    }

    file_user_id.close();
}

void Widget::Show_QList_Users()
{
    QList<Users>::iterator i;
    for(i=users.begin();i!=users.end();++i)
    {
        qDebug()<<i->Get_name()<<i->Get_id()<<i->Get_password()<<i->Get_Books_Numb();
        if(i->is_administrable())
            qDebug()<<"administer";
    }
}

