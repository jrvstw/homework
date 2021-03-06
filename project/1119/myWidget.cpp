#include "myWidget.h"
#include "imgTool.h"
#include "getDefectType.h"

#include <QPainter>
#include <QTimer>
#include <fstream>
#include <vector>

using namespace std;
const QRgb black = 0xFF000000;
const QRgb white = 0xFFFFFFFF;


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

    QRect canvas;
    canvas.setSize(QSize(960, 540));
    canvas.moveCenter(this->rect().center());

    // 1. paint original image

    painter.drawImage(canvas, src);


    // 2. paint dwt result

    vector<int> lumi(src.height());
    for (int y = 0; y < src.height(); y++) {
        for (int x = 0; x < src.width(); x++)
            lumi[y] += qGray(src.pixel(x, y));
        lumi[y] /= src.width();
    }

    int average = 0;
    for (int y = 0; y < src.height(); y++)
        average += lumi[y];
    average /= src.height();

    QImage copy2 = src;
    for (int y = 0; y < src.height(); y++) {
        int d = lumi[y] - average;
        for (int x = 0; x < src.width(); x++) {
            int p = qGray(src.pixel(x, y));
            p -= d;
            if (p > 255)
                p = 255;
            else if (p < 0)
                p = 0;
            copy2.setPixel(x, y, QColor(p, p, p).rgb());
        }
    }

    QImage copy = dwt(copy2, 6, 1024, 1024);


    // 3. paint binary image

    copy = toBinary(copy, autoThreshold(copy));


    // 4. paint processed image

    copy = dilate(copy, 1);
    copy = erode(copy, 1);

    QImage contour = erode(copy, 1);
    for (int y = 0; y < copy.height(); y++)
        for (int x = 0; x < copy.width(); x++)
            contour.setPixel(x, y, copy.pixel(x, y) -
                             (contour.pixel(x, y) & 0xFFFFFF));


    QImage tmpImg(copy);

    for (int y = 0; y < copy.height(); y++)
        for (int x = 0; x < copy.width(); x++)
            if (copy.pixel(x, y) != black) {
                vector<QPoint> object;
                findObject(x, y, &tmpImg, &object);
                QRect bBox(QPoint(x, y), QPoint(x, y));
                QString label;
                defectType type = getDefectType(object, &contour, &bBox);

                if (type == normal)
                    continue;
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

                scaleCoords(&bBox, canvas, copy.rect());
                bBox.translate(canvas.topLeft());
                painter.drawRect(bBox);
                painter.drawText(bBox.topLeft(), label);
            }
}

