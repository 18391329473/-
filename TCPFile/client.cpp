#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QMessageBox>
#include <QHostAddress>

#include <QDebug>
ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    tcpSocket =new QTcpSocket(this);

    isStart = true;
    ui->progressBar->setValue(0);

    setWindowTitle(QStringLiteral("客户端"));

    connect(tcpSocket,&QTcpSocket::readyRead,[=]()
    {

        //取出接收的内容
        QByteArray buf = tcpSocket->readAll();


        if(isStart==true)
        {
            //接收头
            isStart = false;
            //解析头部信息   QString buf="hello##1024"
//            QString str="hello##1024";
//            str.section("##",0,0);


             //初始化
            fileName = QString(buf).section("##",0,0);
            fileSize = QString(buf).section("##",1,1).toInt();
            recvSize = 0;


            //打开文件
            file.setFileName(fileName);

            bool isOk = file.open(QIODevice::WriteOnly);
            if(false == isOk)
            {
                qDebug()<<"WriteOnly Error! 44";

                tcpSocket->disconnectFromHost();    //断开连接
                tcpSocket->close();         //关闭套接字
                return;   //如果打开文件失败，中断函数
            }


            //设置进度条
            ui->progressBar->setMinimum(0);             //最小值
            ui->progressBar->setMaximum(fileSize);      //最大值
            ui->progressBar->setValue(0);               //当前值



        }
        else{

            //文件信息

            qint64 len = file.write(buf);
            if(len>0)
            {
                recvSize += len;

            }

            //实时更新进度条
            ui->progressBar->setValue(recvSize);
            if(recvSize == fileSize)
            {
                //发送给服务器接收完成
                tcpSocket->write("file done");

              //     ui->progressBar->reset();
                file.close();
                QMessageBox::information(this,QStringLiteral("完成"),QStringLiteral("文件接收完成"));
                isStart = true;

            }
        }
    });
}

ClientWidget::~ClientWidget()
{
    delete ui;
}


void ClientWidget::on_buttonConnect_clicked()
{
    //获取服务器的ip和端口
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();

    tcpSocket->connectToHost(QHostAddress(ip),port);
    qDebug()<<QStringLiteral("连接成功");
}


