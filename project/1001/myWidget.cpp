#include "myWidget.h"
#include <QPainter>
#include <QTimer>

myWidget::myWidget(char *pics, int period, QWidget *parent) :
    QWidget(parent)
{
    source = pics;

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer->start(period);

    // test files
    strcpy(test[0], "../pics/impact51.jpg");
    strcpy(test[1], "../pics/impact52.jpg");
    strcpy(test[2], "../pics/impact53.jpg");
    strcpy(test[3], "../pics/impact54.jpg");
    strcpy(test[4], "../pics/water1.jpg");
    /*
    strcpy(xml[0], "../xml/impact51.xml");
    strcpy(xml[1], "../xml/impact52.xml");
    strcpy(xml[2], "../xml/impact53.xml");
    strcpy(xml[3], "../xml/impact54.xml");
    strcpy(xml[4], "../xml/water1.xml");
    */
}

void myWidget::timeout()
{
    index = (index==4)? 0: index + 1;
    this->update();
}


void myWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(test[index]);
    painter.drawPixmap(0,0,width(),height(),pix);

    painter.setPen(QPen(Qt::green, 3));
    painter.drawRect(50+index*100,250,150,150);

    painter.setPen(QPen(Qt::red, 3));
    painter.drawRect(500, 50+index*80,100,150);
}

