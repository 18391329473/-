drawboard::drawboard(QWidget *parent) : QWidget(parent)
{
    pix=new QPixmap(900,600);
    pix->fill(Qt::white);

    fpix=new QPixmap(900,600);
    fpix->fill(Qt::white);
    style=QStringLiteral("直线");

    width=1;
}

//绘图事件
void drawboard::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,0,*pix);

}

void drawboard::mousePressEvent(QMouseEvent *event)
{
    start=event->pos();
    *fpix=*pix;                     //*fpix记录刚开始的位置
}
void drawboard::mouseReleaseEvent(QMouseEvent *event)
{
//    end=event->pos();
//    QPainter p(pix);
//    p.drawLine(start,end);
//    update();
}
void drawboard::mouseMoveEvent(QMouseEvent *event)
{
    if(this->style!=QStringLiteral("曲线"))   //曲线不需要画位图，因为不用清除之前的
    {
         *pix=*fpix;            //移动结束后将最终的位置给pix，fpix记录的是移动的过程路径
    }                           //每次移动将fpix给pix，将之前的地图清掉，直到确定最终位置

    end=event->pos();   //鼠标释放，获取到最终位置
    QPainter p(pix);

    p.setPen(QPen(Qt::yellow,20));




    if(this->style==QStringLiteral("直线"))
    {
         p.drawLine(start,end);
    }
    else if(this->style==QStringLiteral("曲线"))
    {
           p.drawLine(start,end);
           start=end;
           //update();
    }
    else if(this->style==QStringLiteral("矩形"))
    {
        p.drawRect(QRect(start,end));
    }
    else if(this->style==QStringLiteral("椭圆"))
    {
        p.drawEllipse(QRect(start,end));
    }
   // p.drawLine(start,end);
    update();
}
