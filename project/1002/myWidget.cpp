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
    QPixmap pix;
    pix.load(source[index]);
    painter.drawPixmap(0,0,width(),height(),pix);

    xml_document<> doc;
    xml_node<> *root_node;

    ifstream theFile(xmlFile[index]);
    vector<char> buffer((istreambuf_iterator<char>(theFile)),
                        istreambuf_iterator<char>());
    buffer.push_back('\0');

    doc.parse<0>(&buffer[0]);

    root_node = doc.first_node("annotation");

    for (xml_node<> *object_node = root_node->first_node("object");
         object_node;
         object_node = object_node->next_sibling()) {

        xml_node<> *bndbox_node = object_node->first_node("bndbox");
        int xmin = atoi(bndbox_node->first_node("xmin")->value());
        int xmax = atoi(bndbox_node->first_node("xmax")->value());
        int ymin = atoi(bndbox_node->first_node("ymin")->value());
        int ymax = atoi(bndbox_node->first_node("ymax")->value());

        xmin = xmin * width() / 1920;
        xmax = xmax * width() / 1920;
        ymin = ymin * height() / 1080;
        ymax = ymax * height() / 1080;
        painter.setPen(QPen(Qt::green, 3));
        painter.drawRect(xmin, ymin, (xmax-xmin), (ymax-ymin));
    }
}

