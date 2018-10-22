#include "myWidget.h"
#include "imgTool.h"
#include <QPainter>
#include <QTimer>
#include <fstream>
#include <vector>
#include <rapidxml.h>

using namespace rapidxml;
using namespace std;
void visit(int x, int y, QImage *src);

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
    QPainter painter(this);

    const QImage src(source[index]);

    QSize paintSize(src.width() * 2,
                    src.height() * 2);
    paintSize.scale(this->size(), Qt::KeepAspectRatio);

    QRect canvas;
    canvas.setSize(paintSize);
    canvas.moveCenter(this->rect().center());

    QRect subCanvas(canvas.x(),
                    canvas.y(),
                    canvas.width() / 2,
                    canvas.height() / 2);
    painter.drawImage(subCanvas, src);

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

        xmin = xmin * subCanvas.width() / src.width();
        xmax = xmax * subCanvas.width() / src.width();
        ymin = ymin * subCanvas.height() / src.height();
        ymax = ymax * subCanvas.height() / src.height();

        QRect frame(QPoint(xmin, ymin), QPoint(xmax, ymax));
        frame.translate(subCanvas.topLeft());

        painter.setPen(QPen(Qt::green, 1));
        painter.drawRect(frame);
    }

    QImage copy = dwt(src, 5, 1024, 1024);

    subCanvas.moveTo(canvas.x() + canvas.width() / 2,
                     canvas.y());
    painter.drawImage(subCanvas, copy);

    copy = toBinary(copy, 0.13);

    subCanvas.moveTo(canvas.x(),
                     canvas.y() + canvas.height() / 2);
    painter.drawImage(subCanvas, copy);

    copy = erode(copy);

    subCanvas.moveTo(canvas.x() + canvas.width() / 2,
                     canvas.y() + canvas.height() / 2);
    painter.drawImage(subCanvas, copy);

    painter.setPen(QPen(Qt::green, 1));
    for (int y = 0; y < copy.height(); y++)
        for (int x = 0; x < copy.width(); x++)
            if (qGray(copy.pixel(x, y)) == 255) {
                QRect frame(QPoint(x, y), QPoint(x, y));
                findFrame(x, y, &copy, &frame);
                frame.setCoords(frame.left() * subCanvas.width() / copy.width(),
                                frame.top() * subCanvas.height() / copy.height(),
                                frame.right() * subCanvas.width() / copy.width(),
                                frame.bottom() * subCanvas.height() / copy.height());
                frame.translate(subCanvas.topLeft());
                painter.drawRect(frame);
            }
    //copy = copy.convertToFormat(QImage::Format_Mono);
}

