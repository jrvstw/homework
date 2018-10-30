#include "myWidget.h"
#include "imgTool.h"
#include <QPainter>
#include <QTimer>
#include <fstream>
#include <vector>
#include <rapidxml.h>

using namespace rapidxml;
using namespace std;
const QRgb black = 0xFF000000;
const QRgb white = 0xFFFFFFFF;
const QRgb label = 0xFFFFFFFE;
const double pi = 3.1415926;


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

    QSize paintSize(src.size());
    paintSize.scale(this->size(), Qt::KeepAspectRatio);

    QRect canvas;
    canvas.setSize(paintSize);
    canvas.moveCenter(this->rect().center());

    QRect subCanvas(canvas.x(), canvas.y(),
                    canvas.width() / 2, canvas.height() / 2);
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

    subCanvas.moveTo(canvas.x(), canvas.y() + canvas.height() / 2);
    painter.drawImage(subCanvas, copy);

    copy = toBinary(copy, 0.13);

    subCanvas.moveTo(canvas.x() + canvas.width() / 2,
                     canvas.y() + canvas.height() / 2);
    subCanvas = canvas;
    painter.drawImage(subCanvas, src);

    QImage copy2 = erode(copy, 1);
    for (int y = 0; y < copy.height(); y++)
        for (int x = 0; x < copy.width(); x++) {
            if (copy2.pixel(x, y) != copy.pixel(x, y))
                copy.setPixel(x, y, label);
        }


    painter.setPen(QPen(Qt::green, 2));
    for (int y = 0; y < copy.height(); y++)
        for (int x = 0; x < copy.width(); x++)
            if (copy.pixel(x, y) != black) {
                int area = 1;
                int perimeter = 1;
                QRect bBox(QPoint(x, y), QPoint(x, y));
                analyze(x, y, &copy, &area, &perimeter, &bBox);
                if (true
                    && area > 100
                    && bBox.width() < bBox.height() * 3
                    //&& area < bBox.width() * bBox.height() * 0.5
                    && perimeter * perimeter > 4 * pi * area * 2
                    )
                {
                    bBox.setCoords(bBox.left() * subCanvas.width() / copy.width(),
                                   bBox.top() * subCanvas.height() / copy.height(),
                                   bBox.right() * subCanvas.width() / copy.width(),
                                   bBox.bottom() * subCanvas.height() / copy.height());
                    bBox.translate(subCanvas.topLeft());
                    painter.drawRect(bBox);
                }
            }
    //copy = copy.convertToFormat(QImage::Format_Mono);
}

