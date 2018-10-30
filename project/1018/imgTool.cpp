#include "imgTool.h"
using namespace std;
const QRgb black = 0xFF000000;
const QRgb white = 0xFFFFFFFF;
const QRgb label = 0xFFFFFFFE;

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
                copy.setPixel(x, y, white);
            else
                copy.setPixel(x, y, black);
        }
    return copy;
}

QImage erode(QImage source, int d)
{
    QImage extended(source.width() + 2 * d, source.height() + 2 * d,
                    source.format());
    extended.fill(Qt::white);

    for (int y = 0; y < source.height(); y++)
        for (int x = 0; x < source.width(); x++)
            extended.setPixel(x + d, y + d, source.pixel(x, y));

    QImage output(source);
    output.fill(Qt::white);
    for (int y = d; y < source.height() + d; y++)
        for (int x = d; x < source.width() + d; x++) {
            if (extended.pixel(x    , y    ) == black ||
                extended.pixel(x - 1, y    ) == black ||
                extended.pixel(x    , y - 1) == black ||
                extended.pixel(x + 1, y    ) == black ||
                extended.pixel(x    , y + 1) == black)
                output.setPixel(x - d, y - d, black);
        }
    return output;
}

void analyze(int x0, int y0, QImage *src, int *area, int *perimeter,
             QRect *bBox)
{
    queue<QPoint> obj;
    obj.push(QPoint(x0, y0));
    src->setPixel(x0, y0, black);
    while (obj.size() > 0) {
        visit(-1,  0, &obj, src, area, perimeter, bBox);
        visit( 1,  0, &obj, src, area, perimeter, bBox);
        visit( 0, -1, &obj, src, area, perimeter, bBox);
        visit( 0,  1, &obj, src, area, perimeter, bBox);
        visit(-1, -1, &obj, src, area, perimeter, bBox);
        visit(-1,  1, &obj, src, area, perimeter, bBox);
        visit( 1, -1, &obj, src, area, perimeter, bBox);
        visit( 1,  1, &obj, src, area, perimeter, bBox);
        obj.pop();
    }
}

void visit(int dx, int dy, queue<QPoint> *obj, QImage *src, int *area,
           int *perimeter, QRect *bBox)
{
    QPoint p(obj->front().x() + dx,
             obj->front().y() + dy);

    if (src->rect().contains(p) && src->pixel(p) != black) {
        *area = *area + 1;
        if (src->pixel(p) == label)
            *perimeter = *perimeter + 1;
        *bBox = bBox->united(QRect(p, p));
        obj->push(p);
        src->setPixel(p, black);
    }
}

