#include "myWidget.h"
#include "imgTool.h"
#include "getDefectType.h"

#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QString>
#include <fstream>
#include <vector>
#include <rapidxml.h>

using namespace rapidxml;
using namespace std;
const QRgb black = 0xFF000000;
const QRgb white = 0xFFFFFFFF;


myWidget::myWidget(char xmls[][30], char pics[][30], int nPics, int period, QWidget *parent) :
    QWidget(parent)
{
    source = pics;
    nSource = nPics;
    xmlFile = xmls;

    dir = opendir("../pics");
    ent = readdir(dir);
    while (ent != NULL && strstr(ent->d_name, ".jpg") == NULL) {
        ent = readdir(dir);
    }
    if (ent != NULL)
        strcpy(pic_location, ent->d_name);

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
    //const QImage src(pic_location);
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

    QImage copy = dwt(src, 6, 1024, 1024);

    subCanvas.moveTo(canvas.x(), canvas.y() + canvas.height() / 2);
    painter.drawImage(subCanvas, copy);

    // 3. paint binary image

    copy = toBinary(copy, autoThreshold(copy));

    subCanvas.moveTo(canvas.x() + canvas.width() / 2,
                     canvas.y() + canvas.height() / 2);
    painter.drawImage(subCanvas, copy);

    // 4. paint processed image

    copy = dilate(copy, 1);
    copy = erode(copy, 1);

    subCanvas.moveTo(canvas.x() + canvas.width() / 2,
                     canvas.y());

    // 4.2 paint frames on processed image

    QImage contour = erode(copy, 1);
    for (int y = 0; y < copy.height(); y++)
        for (int x = 0; x < copy.width(); x++)
            contour.setPixel(x, y, copy.pixel(x, y) -
                             (contour.pixel(x, y) & 0xFFFFFF));
    //subCanvas = canvas;
    painter.drawImage(subCanvas, contour);
    //painter.drawImage(subCanvas, copy);

    subCanvas.moveTo(canvas.x(), canvas.y());

    QImage tmpImg(copy);

    for (int y = 0; y < copy.height(); y++)
        for (int x = 0; x < copy.width(); x++)
            if (copy.pixel(x, y) != black) {
                vector<QPoint> object;
                findObject(x, y, &tmpImg, &object);
                QRect bBox(QPoint(x, y), QPoint(x, y));
                QString label;
                defectType type = getDefectType(object, &contour, &bBox,
                                                &label);

                if (type == normal)
                    continue;
                else if (type != unrecognized)
                    painter.setPen(QPen(Qt::blue, 2));
                /*
                else if (type == impact)
                    painter.setPen(QPen(Qt::red, 2));
                else if (type == scratch)
                    painter.setPen(QPen(Qt::green, 2));
                else if (type == sponge)
                    painter.setPen(QPen(Qt::yellow, 2));
                else if (type == water)
                    painter.setPen(QPen(Qt::blue, 2));
                else if (type == unrecognized)
                    painter.setPen(QPen(Qt::white, 2));
                    */

                scaleCoords(&bBox, subCanvas, copy.rect());
                bBox.translate(subCanvas.topLeft());
                painter.drawRect(bBox);
                painter.drawText(bBox.topLeft(), label);
            }
    //copy = copy.convertToFormat(QImage::Format_Mono);

    // show statistic
    QFont font;
    font.setPixelSize(20);
    painter.setFont(font);

    int hit, miss, fa;
    switch (index) {
        case 0: case 1: case 2: case 4: case 10: case 11: case 13: case 14:
            hit = 1;
            miss = 0;
            fa = 0;
            break;
        case 3: case 5: case 12:
            hit = 1;
            miss = 1;
            fa = 0;
            break;
        case 6:
            hit = 1;
            miss = 6;
            fa = 2;
            break;
        case 7:
            hit = 3;
            miss = 0;
            fa = 0;
            break;
        case 8:
            hit = 2;
            miss = 1;
            fa = 0;
            break;
        case 9:
            hit = 1;
            miss = 0;
            fa = 1;
            break;
        case 15:
            hit = 1;
            miss = 4;
            fa = 0;
            break;
        case 16: case 18:
            hit = 1;
            miss = 3;
            fa = 0;
            break;
        case 17:
            hit = 2;
            miss = 3;
            fa = 0;
            break;
        case 19:
            hit = 3;
            miss = 0;
            fa = 0;
            break;
    }

    QString string;
    string.append("Hit: ");
    string.append(QString::number(hit));
    string.append("     Miss: ");
    string.append(QString::number(miss));
    string.append("     False Alarm: ");
    string.append(QString::number(fa));

    painter.drawText(subCanvas.bottomLeft(), string);
}

