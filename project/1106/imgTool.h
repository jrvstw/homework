#ifndef IMGTOOL_H
#define IMGTOOL_H

#include <QImage>
#include <QRect>
#include <QColor>
#include <queue>
using namespace std;
enum defectType{normal, impact, scratch, sponge, water};

QImage dwt(QImage source, int level, int width, int height);
QImage toBinary(QImage source, float threshold);
QImage erode(QImage source, int d);
QImage dilate(QImage source, int d);
void analyze(int x, int y, QImage *src, int *area, int *perimeter,
             QRect *bBox);
void visit(int dx, int dy, queue<QPoint> *obj, QImage *src, int *area,
           int *perimeter, QRect *bBox);
float autoThreshold(QImage source);
defectType getDefectType(int area, int perimeter, QRect bBox);
void scaleCoords(QRect *bBox, QRect after, QRect before);

#endif //IMGTOOL_H

