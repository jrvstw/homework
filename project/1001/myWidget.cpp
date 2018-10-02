#include "myWidget.h"
#include <QPainter>
#include <QTimer>

myWidget::myWidget(char pics[][30], int nPics, int period, QWidget *parent) :
    QWidget(parent)
{
    source = pics;
    nSource = nPics;

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer->start(period);
}

void myWidget::timeout()
{
    index = (index == nSource - 1)? 0: index + 1;
    this->update();
}


void myWidget::paintEvent(QPaintEvent *)
{
    // draw pics
    QPainter painter(this);
    QPixmap pix;
    pix.load(source[index]);
    painter.drawPixmap(0,0,width(),height(),pix);

    // draw a green rectangle
    painter.setPen(QPen(Qt::green, 3));
    painter.drawRect(50+index*25,250,150,150);

    // draw a red rectangle
    painter.setPen(QPen(Qt::red, 3));
    painter.drawRect(500, 50+index*20,100,150);
}

