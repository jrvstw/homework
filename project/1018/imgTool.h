#ifndef IMGTOOL_H
#define IMGTOOL_H

#include <QImage>
#include <QRect>
#include <QColor>
#include <QPoint>
#include <queue>
using namespace std;

QImage dwt(QImage source, int level, int width, int height);
QImage toBinary(QImage source, int threshold);
QImage erode(QImage source, int d);
QImage dilate(QImage source, int d);
void findObject(int x, int y, QImage *src, vector<QPoint> *object);
void visit(int dx, int dy, queue<QPoint> *q, vector<QPoint> *object,
           QImage *src);
int autoThreshold(QImage source);
void scaleCoords(QRect *bBox, QRect after, QRect before);

#endif //IMGTOOL_H

