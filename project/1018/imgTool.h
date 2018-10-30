#ifndef IMGTOOL_H
#define IMGTOOL_H

#include <QImage>
#include <QRect>
#include <QColor>
#include <queue>
using namespace std;

QImage dwt(QImage source, int level, int width, int height);
QImage toBinary(QImage source, float threshold);
QImage erode(QImage source, int d);
void analyze(int x, int y, QImage *src, int *area, int *perimeter,
             QRect *bBox);
void visit(int dx, int dy, queue<QPoint> *obj, QImage *src, int *area,
           int *perimeter, QRect *bBox);

#endif //IMGTOOL_H

