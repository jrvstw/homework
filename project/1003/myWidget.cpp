#include "myWidget.h"
#include <QPainter>
#include <QTimer>
#include <fstream>
#include <vector>
#include <rapidxml.h>

using namespace rapidxml;
using namespace std;

myWidget::myWidget(char xmls[][30], char pics[][30], int nPics, int period, QWidget *parent) :
    QWidget(parent)
{
    source = pics;
    nSource = nPics;
    xmlFile = xmls;

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
    QImage img = QImage(source[index]);
    img = img.scaled(width(), height(), Qt::KeepAspectRatio);

    //painter.drawPixmap(0,0,width(),height(),QPixmap(source[index]));
    //painter.drawImage(QRect(0,0,width(),height()), copy);
    painter.drawImage(0,0,img);

    int m[1024][1024] = {0};
    int scale = 1024; // <= 1024
    int level = 5;
    QImage copy = img.scaled(scale, scale, Qt::IgnoreAspectRatio);
    for (int i = 0; i < scale; i++)
        for (int j = 0; j < scale; j++) {
            unsigned int tmp = copy.pixel(i,j);
            m[i][j] = (tmp & 0xFF) + ((tmp>>8) & 0xFF) + ((tmp>>16) & 0xFF);
            m[i][j] /= 3;
        }

    for (int i = 0; i < scale/2; i++)
        for (int j = 0; j < scale/2; j ++)
            m[i][j] = 0;

    for (int i = 0; i < scale; i++)
        for (int j = 0; j < scale; j++) {
            unsigned int tmp;
            tmp = m[i][j] + (m[i][j]<<8) + (m[i][j] << 16);
            copy.setPixel(i, j, tmp);
        }


    xml_document<>  doc;
    xml_node<>      *root_node;
    ifstream        theFile(xmlFile[index]);
    vector<char>    buffer((istreambuf_iterator<char>(theFile)),
                        istreambuf_iterator<char>());

    buffer.push_back('\0');
    doc.parse<0>(&buffer[0]);

    root_node = doc.first_node("annotation");

    for (xml_node<> *object_node = root_node->first_node("object");
         object_node; object_node = object_node->next_sibling()) {

        xml_node<> *bndbox_node = object_node->first_node("bndbox");

        int xmin, xmax, ymin, ymax;
        xmin = atoi(bndbox_node->first_node("xmin")->value())*width()/1920;
        xmax = atoi(bndbox_node->first_node("xmax")->value())*width()/1920;
        ymin = atoi(bndbox_node->first_node("ymin")->value())*height()/1080;
        ymax = atoi(bndbox_node->first_node("ymax")->value())*height()/1080;

        painter.setPen(QPen(Qt::green, 3));
        painter.drawRect(xmin, ymin, (xmax-xmin), (ymax-ymin));
    }
}

