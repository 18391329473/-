#include "mywebengineview.h"
#include<QDebug>
MyWebEngineView::MyWebEngineView(QWidget *parent):QWebEngineView(parent)
{
        setAttribute((Qt::WA_DeleteOnClose));   //相当于析构//关闭这个类的时候析构
        connect(this->page(),&QWebEnginePage::linkHovered,this,&MyWebEngineView::on_linkhovered);
}
QWebEngineView *MyWebEngineView::createWindow(QWebEnginePage::WebWindowType type)
{
    Q_UNUSED(type)
    if(!m_url.isEmpty())
    {
        this->load(QUrl(m_url));
    }


    return nullptr;
}

void MyWebEngineView::on_linkhovered(const QString &url)
{
    m_url.setUrl(url);
}

