#include <PainterWidget.h>

    //設定該類別對外的參數存取
PainterWidget::PainterWidget(char *picturename, QWidget *parent) : QWidget(parent)
{
    this->picturename = picturename;
}

   //QT繪圖事件
void PainterWidget::paintEvent(QPaintEvent *)
{
	qimg = QImage(this ->picturename);
        QPainter painter(this);
	painter.drawImage(0, 0, qimg);
}

