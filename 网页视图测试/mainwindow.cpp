#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QPixmap>
#include "mywebengineview.h"
/*
 * 本周练习：
 * 1.两种布局使用：QHBoxLayout、QVBoxLayout、addWidget()、addItem()
 * 2.信号与槽使用：connect()、disconnect()、SIGNAL()、SLOT()、signals、slots
 * 3.了解输出调试信息 QDebug
 * 4.实现一个浏览器：后退、前进、刷新、停止功能
 * 5.写代码相关注释
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

    , m_web_view(new MyWebEngineView(this))

    , m_url_edit(new QLineEdit(this))

{
    ui->setupUi(this);

    /**
      初始化布局
      **/
    //创建主布局
    this->setWindowIcon(QIcon(":/123.jpg"));
    this->setWindowTitle(QStringLiteral("橙汁浏览器"));
    QVBoxLayout *layout_main = new QVBoxLayout;
    //创建顶部布局
    QHBoxLayout *layout_top = new QHBoxLayout;

    //TODO 添加按钮：后退、前进、刷新、停止

    //添加后退按钮
    QPushButton *button_back = new QPushButton(QStringLiteral(" "));
    layout_top->addWidget(button_back);
    QPixmap pix(":/121.jpg");
    button_back->setIcon(pix);
   // button_back->move(100,0);

    //添加前进按钮
    QPushButton *button_enter = new QPushButton(QStringLiteral("  "));
    layout_top->addWidget(button_enter);
    QPixmap pix1(":/122.jpg");
    button_enter->setIcon(pix1);


    //添加刷新按钮
    QPushButton *button_ref = new QPushButton(QStringLiteral("  "));
    layout_top->addWidget(button_ref);
    QPixmap pix2(":/124.jpg");
    button_ref->setIcon(pix2);


    //添加停止按钮
    QPushButton *button_stop = new QPushButton(QStringLiteral("  "));
    layout_top->addWidget(button_stop);

    QPixmap pix3(":/125.jpg");
    button_stop->setIcon(pix3);

    //添加地址输入栏
    layout_top->addWidget(new QLabel(QStringLiteral("地址:")));
    layout_top->addWidget(m_url_edit);

    //添加浏览按钮
    QPushButton *button_view = new QPushButton(QStringLiteral("浏览"));
    layout_top->addWidget(button_view);



    //加入到主布局
    layout_main->addItem(layout_top);
    button_stop->hide();
    layout_main->addWidget(m_web_view);     //m_web_view浏览界面
    //每个Widget只能有一个布局
    if (ui->centralwidget->layout())
        delete ui->centralwidget->layout();
    ui->centralwidget->setLayout(layout_main);
    this->setStyleSheet("background-color:pink");


    /**
      连接信号与槽
      **/
    //TODO 了解常用连接信号方法，并说明
    //1.网页的标题发生变化，重置主窗口标题
    connect(m_web_view, &QWebEngineView::titleChanged, this, &MainWindow::setWindowTitle);
    //2.网页加载完成，可以作为信号进行传递
    connect(m_web_view, &QWebEngineView::loadFinished, this, &MainWindow::pageLoaded);
    //3.网页加载完成，作为槽函数传递
    connect(m_web_view, &QWebEngineView::loadFinished, this, &MainWindow::slotLoadFinished);



    //4.点击浏览按钮，当前网页停止，加载输入的url网址，状态栏显示加载信息
    connect(button_view, &QPushButton::clicked, this, [=](){
        m_web_view->stop();
        m_web_view->load(QUrl(m_url_edit->text()));
        ui->statusbar->showMessage(QStringLiteral("浏览：") + m_url_edit->text());
        qDebug()<<"view url: "<<m_url_edit->text();
    });
    //连接后退信号
    connect(button_back, &QPushButton::clicked, m_web_view, &QWebEngineView::back);
   /* connect(button_back, &QPushButton::clicked,[=](){
       m_web_view->back();
       button_ref->hide();
       button_stop->show();
       connect(button_stop, &QPushButton::clicked, [=](){
           m_web_view->stop();
           button_stop->hide();
           button_ref->show();
       });
       connect(this,&MainWindow::pageLoaded,[=](){
           //m_web_view->stop();
           button_stop->hide();
           button_ref->show();
       });
        //m_url_edit->setText(MyWebEngineView::m_url);
    });
*/
    //连接前进信号
   connect(button_enter, &QPushButton::clicked, m_web_view, &QWebEngineView::forward);
  //  disconnect(button_enter, &QPushButton::clicked, m_web_view, &QWebEngineView::forward);  //  信号可以断开连接
   /*
    connect(button_enter, &QPushButton::clicked, [=](){
        m_web_view->forward();
        button_ref->hide();
        button_stop->show();
        connect(button_stop, &QPushButton::clicked, [=](){
            m_web_view->stop();
            button_stop->hide();
            button_ref->show();
        });
        connect(this,&MainWindow::pageLoaded,[=](){
            m_web_view->stop();
            button_stop->hide();
            button_ref->show();
        });
    });
*/
    //刷新和停止
    connect(button_ref,&QPushButton::clicked,[=](){
            m_web_view->reload();
            button_ref->hide();
            button_stop->show();

            connect(this,&MainWindow::pageLoaded,[=](){
                //m_web_view->stop();
                button_stop->hide();
                button_ref->show();
            });
            connect(button_stop, &QPushButton::clicked, [=](){
                m_web_view->stop();
                button_stop->hide();
                button_ref->show();
            });
    });



    //连接刷新信号
    //connect(button_ref, &QPushButton::clicked, m_web_view, &QWebEngineView::reload);
    //连接停止信号
   // connect(button_stop, &QPushButton::clicked, m_web_view, &QWebEngineView::stop);
    /**
      初始化控件属性
      **/
    m_url_edit->setText("https://www.baidu.com.cn/");
    m_web_view->load(QUrl(m_url_edit->text()));
}
void MainWindow::slotLoadFinished(bool)
{
    ui->statusbar->showMessage(QStringLiteral("完成"));
}
MainWindow::~MainWindow()
{
    delete ui;
}



