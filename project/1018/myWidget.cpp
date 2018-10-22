#include "myWidget.h"
#include <QPainter>
#include <QTimer>
#include <fstream>
#include <vector>
#include <rapidxml.h>

using namespace rapidxml;
using namespace std;
QImage dwt(QImage source, int level, int width, int height);
QImage toBinary(QImage source, float threshold);
QImage erode(QImage source);
QRect findFrame(int x, int y, QImage *src, QRect *frame);
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

QRect findFrame(int x, int y, QImage *src, QRect *frame)
{
    return *frame;
}

QImage erode(QImage source)
{
    QImage extended(source.width() + 6,
                    source.height() + 6,
                    source.format());
    extended.fill(Qt::white);
    for (int y = 0; y < source.height(); y++)
        for (int x = 0; x < source.width(); x++)
            extended.setPixel(x + 3, y + 3, source.pixel(x, y));
    QImage output(source);
    output.fill(Qt::white);
    QRgb black = QColor(0, 0, 0).rgb();
    for (int y = 3; y < source.height() + 3; y++)
        for (int x = 3; x < source.width() + 3; x++) {
            if (extended.pixel(x    , y    ) == black ||
                extended.pixel(x - 1, y    ) == black ||
                extended.pixel(x    , y - 1) == black ||
                extended.pixel(x + 1, y    ) == black ||
                extended.pixel(x    , y + 1) == black)
                output.setPixel(x - 3, y - 3, black);
        }
    return output;
}

QImage dwt(QImage source, int level, int width, int height)
{
    QImage copy = source.scaled(width, height, Qt::IgnoreAspectRatio);

    int m[1024][1024];
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            m[y][x] = qGray(copy.pixel(x, y));

    int k = 0;
    int a, b, c, d;
    for (int i = 0; i < level; i++) {
        k = (k == 0)? 1: (k << 1);
        for (int y = 0; y < height; y += (k << 1))
            for (int x = 0; x < width; x += (k << 1)) {
                a = m[y    ][x    ];
                b = m[y    ][x + k];
                c = m[y + k][x    ];
                d = m[y + k][x + k];
                m[y    ][x    ] = a + b + c + d;
                m[y    ][x + k] = a - b + c - d;
                m[y + k][x    ] = a + b - c - d;
                m[y + k][x + k] = a - b - c + d;
            }
    }

    for (int y = 0; y < height; y += (k << 1))
        for (int x = 0; x < width; x += (k << 1)) {
            m[y    ][x    ] = 0;
            //m[y    ][x + k] *= 2;
            //m[y + k][x    ] *= 2;
            //m[y + k][x + k] *= 2;
        }

    for (int i = 0; i < level; i++) {
        for (int y = 0; y < height; y+= (k << 1))
            for (int x = 0; x < width; x += (k << 1)) {
                a = m[y    ][x    ];
                b = m[y    ][x + k];
                c = m[y + k][x    ];
                d = m[y + k][x + k];
                m[y    ][x    ] = (a + b + c + d) >> 2;
                m[y    ][x + k] = (a - b + c - d) >> 2;
                m[y + k][x    ] = (a + b - c - d) >> 2;
                m[y + k][x + k] = (a - b - c + d) >> 2;
            }
        k >>= 1;
    }

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++) {
            if (-255 <= m[y][x] && m[y][x] <= 0)
                m[y][x] = -m[y][x];
            else
                m[y][x] = 0;
            copy.setPixel(x, y, QColor(m[y][x], m[y][x], m[y][x]).rgb());
        }

    return copy;
}

QImage toBinary(QImage source, float threshold)
{
    QImage copy = source;
    int    thre = (int)(threshold * 255);
    for (int y = 0; y < copy.height(); y++)
        for (int x = 0; x < copy.width(); x++) {
            if (qGray(copy.pixel(x, y)) >= thre)
                copy.setPixel(x, y, QColor(255,255,255).rgb());
            else
                copy.setPixel(x, y, QColor(0,0,0).rgb());
        }
    return copy;
}

