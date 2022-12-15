#include "serverwidget.h"
#include "ui_serverwidget.h"
#include <QDateTime>

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    tcpServer = NULL;
    tcpSocket = NULL;

    //监听套接字,指定父对象，让其自动回收空间
    tcpServer = new QTcpServer(this);

    tcpServer->listen(QHostAddress::Any,8888);
    setWindowTitle(QStringLiteral("服务器：8888"));

    connect(tcpServer,&QTcpServer::newConnection,[=]()
    {
        //取出建立好连接的套接字
        tcpSocket=tcpServer->nextPendingConnection();
        //获取对方的IP和端口
        QString ip = tcpSocket->peerAddress().toString();
        qint16 port = tcpSocket->peerPort();
        QString temp = QString(QStringLiteral("['%1'，'%2']:成功连接")).arg(ip).arg(port);

      //  ui->textEditRead->setText(temp);// ui->textEditRead->setAlignment(Qt::AlignLeft);
        connect(tcpSocket,&QTcpSocket::readyRead,[=](){
            //从通信套接字中取出内容
            QByteArray array = tcpSocket->readAll();
            QDateTime current_date_time =QDateTime::currentDateTime();
            QString current_date =current_date_time.toString("yyyy/MM/dd hh:mm:ss");

            ui->textEditRead->append(QStringLiteral("[%1:%2]").arg(QStringLiteral("客户端")).arg(current_date));
            ui->textEditRead->setAlignment(Qt::AlignLeft);
            ui->textEditRead->append(array);
            ui->textEditRead->setAlignment(Qt::AlignLeft);
        });
    });

    ui->buttonSend->setShortcut(QKeySequence(tr("ctrl+return")));
}

ServerWidget::~ServerWidget()
{
    delete ui;
}


void ServerWidget::on_buttonSend_clicked()
{
    if(NULL==tcpSocket)
    {
        return;
    }

     //获取编辑区内容
    QString str=ui->textEditWrite->toPlainText();
    //给对方发送数据，使用套接字是tcpSocket
    tcpSocket->write(str.toUtf8().data());
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy/MM/dd hh:mm:ss");

    ui->textEditRead->append(QStringLiteral("[%1:%2]").arg(QStringLiteral("服务器")).arg(current_date));
    ui->textEditRead->setAlignment(Qt::AlignRight);
    ui->textEditRead->append(str);
    ui->textEditRead->setAlignment(Qt::AlignRight);
   // ui->textEditWrite->clear();
}

void ServerWidget::on_buttonClose_clicked()
{
    if(NULL==tcpSocket)
    {
        return;
    }
    //主动和客户端断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket = NULL;
    ui->textEditRead->setText(QStringLiteral("服务器断开连接！！！！！"));
}

