#include "imgTool.h"

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

QRect findFrame(int x, int y, QImage *src, QRect *frame)
{
    return *frame;
}

