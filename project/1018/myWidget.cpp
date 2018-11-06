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
    this->update();
}

void myWidget::mousePressEvent(QMouseEvent *)
{
    index = (index == nSource - 1)? 0: index + 1;
    this->update();
}

void myWidget::paintEvent(QPaintEvent *)
{
    // 0. setup
    QPainter painter(this);
    const QImage src(source[index]);

    QSize paintSize(src.size());
    paintSize.scale(this->size(), Qt::KeepAspectRatio);

    QRect canvas;
    canvas.setSize(paintSize);
    canvas.moveCenter(this->rect().center());

    // 1. paint original image

    QRect subCanvas(canvas.x(), canvas.y(),
                    canvas.width() / 2, canvas.height() / 2);
    painter.drawImage(subCanvas, src);

    // 1.2 paint frames on original image

    painter.setPen(QPen(Qt::red, 2));

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

        QRect frame;
        frame.setCoords(atoi(bndbox_node->first_node("xmin")->value()),
                        atoi(bndbox_node->first_node("ymin")->value()),
                        atoi(bndbox_node->first_node("xmax")->value()),
                        atoi(bndbox_node->first_node("ymax")->value()));
        scaleCoords(&frame, subCanvas, src.rect());
        frame.translate(subCanvas.topLeft());

        painter.drawRect(frame);
    }

    // 2. paint dwt result

    QImage copy = dwt(src, 5, 1024, 1024);

    subCanvas.moveTo(canvas.x(), canvas.y() + canvas.height() / 2);
    painter.drawImage(subCanvas, copy);

    // 3. paint binary image

    copy = toBinary(copy, autoThreshold(copy));

    subCanvas.moveTo(canvas.x() + canvas.width() / 2,
                     canvas.y() + canvas.height() / 2);
    painter.drawImage(subCanvas, copy);

    // 4. paint processed image

    /*
    copy = dilate(copy, 1);
    copy = dilate(copy, 1);
    copy = dilate(copy, 1);
    copy = dilate(copy, 1);
    copy = erode(copy, 1);
    copy = erode(copy, 1);
    copy = erode(copy, 1);
    copy = erode(copy, 1);
    */

    subCanvas.moveTo(canvas.x() + canvas.width() / 2,
                     canvas.y());
    painter.drawImage(subCanvas, copy);

    //subCanvas = canvas;
    QImage copy2 = erode(copy, 1);
    for (int y = 0; y < copy.height(); y++)
        for (int x = 0; x < copy.width(); x++) {
            if (copy2.pixel(x, y) != copy.pixel(x, y))
                copy.setPixel(x, y, label);
        }

    // 4.2 paint frames on processed image

    painter.setPen(QPen(Qt::blue, 2));
    for (int y = 0; y < copy.height(); y++)
        for (int x = 0; x < copy.width(); x++)
            if (copy.pixel(x, y) != black) {
                int area = 1;
                int perimeter = 1;
                QRect bBox(QPoint(x, y), QPoint(x, y));
                analyze(x, y, &copy, &area, &perimeter, &bBox);
                defectType type = getDefectType(area, perimeter, bBox);
                if (type == normal)
                    continue;
                else if (type == impact)
                    painter.setPen(QPen(Qt::red, 2));
                else if (type == scratch)
                    painter.setPen(QPen(Qt::green, 2));
                else if (type == sponge)
                    painter.setPen(QPen(Qt::yellow, 2));
                else if (type == impact)
                    painter.setPen(QPen(Qt::blue, 2));
                scaleCoords(&bBox, subCanvas, copy.rect());
                bBox.translate(subCanvas.topLeft());
                painter.drawRect(bBox);
            }
    //copy = copy.convertToFormat(QImage::Format_Mono);
}

