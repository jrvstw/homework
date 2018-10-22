#ifndef IMGTOOL_H
#define IMGTOOL_H

#include <QImage>
#include <QRect>
#include <QColor>

QImage dwt(QImage source, int level, int width, int height);
QImage toBinary(QImage source, float threshold);
QImage erode(QImage source);
QRect findFrame(int x, int y, QImage *src, QRect *frame);

#endif //IMGTOOL_H
