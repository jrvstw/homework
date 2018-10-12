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

    if (period > 0) {
        timer = new QTimer(this);
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
        timer->start(period);
    }
}

void myWidget::timeout()
{
    index = (index == nSource - 1)? 0: index + 1;
    // find defects
    this->update();
}

void myWidget::mousePressEvent(QMouseEvent *)
{
    index = (index == nSource - 1)? 0: index + 1;
    // find defects
    this->update();
}

void myWidget::paintEvent(QPaintEvent *)
{
    const QImage img(source[index]);

    QRect canvas;
    canvas.setSize(img.scaled(this->size(), Qt::KeepAspectRatio).size());
    canvas.moveCenter(this->rect().center());

    int m[1024][1024] = {0};
    int scale = 1024; // <= 1024
    int level = 5;
    QImage copy = img.scaled(scale, scale, Qt::IgnoreAspectRatio);

    for (int i = 0; i < scale; i++)
        for (int j = 0; j < scale; j++) {
            unsigned int tmp = copy.pixel(i,j);
            int r = (tmp & 0xFF0000) >> 16,
                g = (tmp & 0x00FF00) >> 8,
                b = (tmp & 0x0000FF);
            m[i][j] = (int)(0.3 * r + 0.59 * g + 0.11 * b);
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

    QPainter painter(this);

    painter.drawImage(canvas, img);

    // read xml
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

        int xmin = atoi(bndbox_node->first_node("xmin")->value());
        int xmax = atoi(bndbox_node->first_node("xmax")->value());
        int ymin = atoi(bndbox_node->first_node("ymin")->value());
        int ymax = atoi(bndbox_node->first_node("ymax")->value());

        xmin = xmin * canvas.width() / img.width();
        xmax = xmax * canvas.width() / img.width();
        ymin = ymin * canvas.height() / img.height();
        ymax = ymax * canvas.height() / img.height();

        QRect frame(QPoint(xmin, ymin), QPoint(xmax, ymax));
        frame.translate(canvas.topLeft());

        painter.setPen(QPen(Qt::green, 2));
        painter.drawRect(frame);
    }
}

