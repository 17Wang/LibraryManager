#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QDialog>
#include <QLabel>
#include <QFile>
#include <QString>
#include <QList>

#include "widget.h"
#include "users.h"
#include "pageadminister.h"
#include "pageuser.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //===================主要的操作函数
    void Initial_Layout();//初始化布局
    void Readin_Users_Informations();//读取用户信息

private:
    Ui::Widget *ui;
    PageUser *main_page_user;//user的终极主界面
    PageAdminister *main_page_administer;//administer的终极主界面

public://终极主界面的初始化
    void Initial_Page_User();
    void Initial_Page_Administer();

private://==================登录界面及其控件
    QLabel *title;

    QLineEdit *user_id;
    QLineEdit *pass_word;

    QRadioButton *administer;
    QRadioButton *user;

    QPushButton *Login;

public://===================登录界面操作及其函数
    void Login_Button();
      //按下Login后响应
      //需要返回user_id,pass_word
      //输入错误，弹出警告窗口
      //需要知道选择了administer还是user
      //跳转界面不一样

    QString &GetUserName();
    QString &GetPassWord();

private://===================自定义类
    QList<Users> users;

public://===================自定义类操作函数
    void Show_QList_Users();
};

#endif // WIDGET_H
