#include "imgTool.h"
#include <vector>
#include <cmath>
using namespace std;
const QRgb black = 0xFF000000;
const QRgb white = 0xFFFFFFFF;


QImage dwt(QImage src, int level, int width, int height)
{
    QImage copy = src.scaled(width, height, Qt::IgnoreAspectRatio);

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

    return copy.scaled(src.width()/2, src.height()/2, Qt::IgnoreAspectRatio);
}

QImage toBinary(QImage source, int threshold)
{
    QImage copy = source;
    for (int y = 0; y < copy.height(); y++)
        for (int x = 0; x < copy.width(); x++) {
            if (qGray(copy.pixel(x, y)) >= threshold)
                copy.setPixel(x, y, white);
            else
                copy.setPixel(x, y, black);
        }
    return copy;
}

int autoThreshold(QImage source)
{
    int histogram[256] = {0};
    for (int y = 0; y < source.height(); y++)
        for (int x = 0; x < source.width(); x++) {
            histogram[ qGray(source.pixel(x, y)) ]++;
        }
    int threshold = 255;
    while(histogram[threshold] == 0)
        threshold--;
    return threshold * 50 / 100;
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
            if (d < 2)
                continue;
            if (extended.pixel(x + 2, y    ) == black ||
                extended.pixel(x + 1, y + 1) == black ||
                extended.pixel(x    , y + 2) == black ||
                extended.pixel(x - 1, y + 1) == black ||
                extended.pixel(x - 2, y    ) == black ||
                extended.pixel(x - 1, y - 1) == black ||
                extended.pixel(x    , y - 2) == black ||
                extended.pixel(x + 1, y - 1) == black)
                output.setPixel(x - d, y - d, black);
            if (d < 3)
                continue;
            if (extended.pixel(x + 3, y    ) == black ||
                extended.pixel(x + 2, y + 1) == black ||
                extended.pixel(x + 1, y + 2) == black ||
                extended.pixel(x    , y + 3) == black ||
                extended.pixel(x - 1, y + 2) == black ||
                extended.pixel(x - 2, y + 1) == black ||
                extended.pixel(x - 3, y    ) == black ||
                extended.pixel(x - 2, y - 1) == black ||
                extended.pixel(x - 1, y - 2) == black ||
                extended.pixel(x    , y - 3) == black ||
                extended.pixel(x + 1, y - 2) == black ||
                extended.pixel(x + 2, y - 1) == black)
                output.setPixel(x - d, y - d, black);
            if (d < 4)
                continue;
            if (extended.pixel(x + 4, y    ) == black ||
                extended.pixel(x + 3, y + 1) == black ||
                extended.pixel(x + 2, y + 2) == black ||
                extended.pixel(x + 1, y + 3) == black ||
                extended.pixel(x    , y + 4) == black ||
                extended.pixel(x - 1, y + 3) == black ||
                extended.pixel(x - 2, y + 2) == black ||
                extended.pixel(x - 3, y + 1) == black ||
                extended.pixel(x - 4, y    ) == black ||
                extended.pixel(x - 3, y - 1) == black ||
                extended.pixel(x - 2, y - 2) == black ||
                extended.pixel(x - 1, y - 3) == black ||
                extended.pixel(x    , y - 4) == black ||
                extended.pixel(x + 1, y - 3) == black ||
                extended.pixel(x + 2, y - 2) == black ||
                extended.pixel(x + 3, y - 1) == black)
                output.setPixel(x - d, y - d, black);
        }
    return output;
}

QImage dilate(QImage source, int d)
{
    QImage tmp(source);
    for (int y = 0; y < source.height(); y++)
        for (int x = 0; x < source.width(); x++)
            tmp.setPixel(x, y, white - (0x00FFFFFF & tmp.pixel(x, y)));
    tmp = erode(tmp, d);
    for (int y = 0; y < source.height(); y++)
        for (int x = 0; x < source.width(); x++)
            tmp.setPixel(x, y, white - (0x00FFFFFF & tmp.pixel(x, y)));
    return tmp;
}

void findObject(int x0, int y0, QImage *src, vector<QPoint> *object)
{
    object->push_back(QPoint(x0, y0));
    queue<QPoint> q;
    q.push(QPoint(x0, y0));
    src->setPixel(x0, y0, black);
    while (q.size() > 0) {
        visit( 1,  0, &q, object, src);
        visit( 0,  1, &q, object, src);
        visit(-1,  0, &q, object, src);
        visit( 0, -1, &q, object, src);
        visit( 1,  1, &q, object, src);
        visit(-1,  1, &q, object, src);
        visit(-1, -1, &q, object, src);
        visit( 1, -1, &q, object, src);
        visit( 2,  0, &q, object, src);
        visit( 0,  2, &q, object, src);
        visit(-2,  0, &q, object, src);
        visit( 0, -2, &q, object, src);
        visit( 3,  0, &q, object, src);
        visit( 2,  1, &q, object, src);
        visit( 1,  2, &q, object, src);
        visit( 0,  3, &q, object, src);
        visit(-1,  2, &q, object, src);
        visit(-2,  1, &q, object, src);
        visit(-3,  0, &q, object, src);
        visit(-2, -1, &q, object, src);
        visit(-1, -2, &q, object, src);
        visit( 0, -3, &q, object, src);
        visit( 1, -2, &q, object, src);
        visit( 2, -1, &q, object, src);
        q.pop();
    }
}

void visit(int dx, int dy, queue<QPoint> *q, vector<QPoint> *object,
           QImage *src)
{
    QPoint p(q->front().x() + dx,
             q->front().y() + dy);
    if (src->rect().contains(p) && src->pixel(p) != black) {
        q->push(p);
        object->push_back(p);
        src->setPixel(p, black);
    }
}

defectType getDefectType(vector<QPoint> object, QImage *contour,
                         QRect *bBox, QString *label)
{
    int area = object.size();

    int perimeter = 0;
    double xSum = 0, ySum = 0, xxSum = 0, xySum = 0, yySum = 0;

    for (int i = 0; i < area; i++) {
        QPoint p(object[i].x(), object[i].y());
        *bBox = bBox->united(QRect(p, p));
        if (contour->pixel(p) == white)
            perimeter++;
        xSum += p.x();
        ySum += p.y();
        xxSum += p.x() * p.x();
        xySum += p.x() * p.y();
        yySum += p.y() * p.y();
    }

    if (area < 40 || area > 3000)
        return normal;

    int convexArea;
    double convexPerimeter;
    getConvex(object, &convexArea, &convexPerimeter);
    double xMean = xSum / area,
           yMean = ySum / area,
           nSxSx = xxSum - xMean * xSum,
           nSySy = yySum - yMean * ySum,
           orientation = -(xySum - xMean*ySum) / nSxSx,
           correlation = orientation * sqrt(nSxSx / nSySy);

    double compactness = convexPerimeter*convexPerimeter/12.56/convexArea;
    label->setNum(compactness);

    if (true &&
        compactness > 1.9 &&
        true)
        return scratch;

    if (true &&
        compactness < 1.3 &&
        true)
        return water;

    return sponge;

    //if (convexArea > bBox->width() * bBox->height() * 1)
    if (area < bBox->width() * bBox->height() * 0.3 &&
        perimeter < area * 0.4)
            return scratch;

    if (abs(orientation) > 0.2 &&
        abs(orientation) < 3 &&
        area < bBox->width() * bBox->height() * 0.4)
        return impact;

    /*
    if (area > 200 &&
        area < bBox->width() * bBox->height() * 0.4 &&
        //perimeter < area * 0.3 &&
        orientation < -0.5 &&
        true)
        return impact;
        */


    return unrecognized;

    if (area - perimeter < 200 &&
        perimeter * 2 > area)
        return water;


    if (bBox->width() > bBox->height() * 2 &&
        area > bBox->width() * bBox->height() * 0.3)
        return water;

    if (area > 80 &&
        perimeter > area * 0.5 &&
        true)
        return scratch;
    return normal;
}

void scaleCoords(QRect *bBox, QRect after, QRect before)
{
    bBox->setCoords(bBox->left()  * after.width() / before.width(),
                    bBox->top()    * after.height() / before.height(),
                    bBox->right() * after.width() / before.width(),
                    bBox->bottom() * after.height() / before.height());
}

int cross(QPoint O, QPoint A, QPoint B)
{
    return (A.x()-O.x()) * (B.y()-A.y()) - (B.x()-A.x()) * (A.y()-O.y());
}

int compare(const void* C, const void* D)
{
    QPoint A = *(QPoint *)C,
           B = *(QPoint *)D;
    if (A.x() != B.x())
        return A.x() - B.x();
    else
        return A.y() - B.y();
}

void convexHull(QPoint convex[10000], int *top, QPoint input[10000], int ninput)
{
    int i = 0;
    for (i = 0; i < ninput; i++) {
        while (*top > 0 &&
               cross(convex[*top - 1], convex[*top], input[i]) <=0)
            (*top)--;
        convex[++(*top)] = input[i];
    }
    int middle = *top;
    for (i = ninput - 2; i >=0; i--) {
        while (*top > middle &&
               cross(convex[*top - 1], convex[*top], input[i]) <= 0)
            (*top)--;
        convex[++(*top)] = input[i];
    }
    (*top)--;
}

void getConvex(vector<QPoint> object, int *area, double *perimeter)
{
    int size = object.size();
    QPoint array[10000];
    for (int i = 0; i < size; i++)
        array[i] = object[i];
    qsort(array, size, sizeof(QPoint), compare);
    QPoint convex[10000];
    int top = -1;
    convexHull(convex, &top, array, size);
    *area = (convex[top].x() * convex[0].y() -
             convex[top].y() * convex[0].x());
    int dx = convex[top].x() - convex[0].x(),
        dy = convex[top].y() - convex[0].y();
    *perimeter = sqrt(dx * dx + dy * dy);
    for (int i = 0; i <= top - 1; i++) {
        *area += (convex[i].x() * convex[i + 1].y() -
                  convex[i].y() * convex[i + 1].x());
        dx = convex[i + 1].x() - convex[i].x();
        dy = convex[i + 1].y() - convex[i].y();
        *perimeter += sqrt(dx * dx + dy * dy);
    }
   *area = abs(*area) / 2;
}

