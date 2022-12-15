#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QHostAddress>
#include <QDateTime>
#include <QDebug>
ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    tcpSocket=NULL;

    setWindowTitle(QStringLiteral("客户端"));
    //分配空间，指定父对象
    tcpSocket=new QTcpSocket(this);
    QString ip="127.0.0.1";
    QString port="8888";
    ui->lineEditIp->setText(ip);
    ui->lineEditPort->setText(port);

    connect(tcpSocket,&QTcpSocket::connected,[=](){
        ui->textEditRead->setText(QStringLiteral("成功和服务器建立连接"));
    });

    connect(tcpSocket,&QTcpSocket::readyRead,[=](){

        //获取对方发送的内容
        QByteArray array = tcpSocket->readAll();
        QDateTime current_date_time =QDateTime::currentDateTime();
        QString current_date =current_date_time.toString("yyyy/MM/dd hh:mm:ss");

        ui->textEditRead->append(QStringLiteral("[%1:%2]").arg(QStringLiteral("服务器")).arg(current_date));
        ui->textEditRead->append(array);


    });
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_pushButtonConnect_clicked()
{
    QString ip=ui->lineEditIp->text();
    qint16 port=ui->lineEditPort->text().toInt();

    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip),port);

}

void ClientWidget::on_pushButtonSend_clicked()
{
    //获取编辑框内容
    QString str =ui->textEditWrite->toPlainText();
    //发送数据
    tcpSocket->write(str.toUtf8().data());
}

void ClientWidget::on_pushButtonClose_clicked()
{
    if(NULL==tcpSocket)
    {
        return;
    }
    //主动和客户端断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    ui->textEditRead->setText(QStringLiteral("请连接服务器！！！！！"));
}
