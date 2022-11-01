#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QLabel>
#include<QComboBox>
#include<QToolBar>
#include<QPushButton>
#include<QColorDialog>
#include<QSpinBox>
#include<QMainWindow>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->setWindowTitle(QStringLiteral("欢迎来到Ycz的画板"));
    this->setWindowIcon(QIcon(":/pig.jpg"));

    this->resize(900,600);
    QLabel *lab=new QLabel(QStringLiteral("线型 "),this);
    QComboBox *cmb=new QComboBox(lab);
    cmb->addItem(QStringLiteral("直线"));
    cmb->addItem(QStringLiteral("曲线"));
    cmb->addItem(QStringLiteral("矩形"));
    cmb->addItem(QStringLiteral("椭圆"));


    ui->toolBar->addWidget(lab);
    ui->toolBar->addWidget(cmb);
    QLabel *lab1=new QLabel(QStringLiteral(" 线宽 "),this);
    QSpinBox *sb=new QSpinBox(lab1);
    ui->toolBar->addWidget(lab1);
    ui->toolBar->addWidget(sb);

    ui->toolBar->addSeparator();
    QPushButton *color=new QPushButton(QStringLiteral("调色板"));
    ui->toolBar->addWidget(color);
   // ui->toolBar->addAction(QStringLiteral("直线"));
    ui->toolBar->addSeparator();
    QPushButton *clear=new QPushButton(QStringLiteral("清空"));
    ui->toolBar->addWidget(clear);

    drawboard *d=new drawboard;
    this->setCentralWidget(d);

    //线型
    connect(cmb,&QComboBox::currentTextChanged,[=](QString text){
        d->style=text;
    });

    //线宽
   // connect(sb,QSpinBox::valueChanged,)   valueChanged函数有重载，因此选择指针
    void (QSpinBox:: *p)(int i)=&QSpinBox::valueChanged;  //指针p指向该函数
    connect(sb,p,[=](int i){
        d->width=i;
    });
    //颜色
    connect(color,&QPushButton::clicked,[=](){
       d->c=QColorDialog::getColor();
    });
    connect(clear,&QPushButton::clicked,[=](){
        d->pix->fill();
        update();
    });
}
MainWindow::~MainWindow()
{
    delete ui;
}

