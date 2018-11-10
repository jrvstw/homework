#ifndef IMGTOOL_H
#define IMGTOOL_H

#include <QImage>
#include <QRect>
#include <QColor>
#include <QPoint>
#include <queue>
using namespace std;
enum defectType{normal, impact, scratch, sponge, water, unrecognized};

QImage dwt(QImage source, int level, int width, int height);
QImage toBinary(QImage source, int threshold);
QImage erode(QImage source, int d);
QImage dilate(QImage source, int d);
void findObject(int x, int y, QImage *src, vector<QPoint> *object);
void visit(int dx, int dy, queue<QPoint> *q, vector<QPoint> *object,
           QImage *src);
int autoThreshold(QImage source);
defectType getDefectType(vector<QPoint> object, QImage *contour, QRect *bBox);
void scaleCoords(QRect *bBox, QRect after, QRect before);
int cross(QPoint O, QPoint A, QPoint B);
int compare(const void* C, const void* D);
void convexHull(QPoint convex[10000], int *top, QPoint input[10000], int ninput);
int getConvexArea(vector<QPoint> object);

#endif //IMGTOOL_H

