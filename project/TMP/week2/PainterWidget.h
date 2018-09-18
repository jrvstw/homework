#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H
#include <QtGui/QApplication>
#include <QTimer>
#include <QWidget>
#include <QPainter>

class PainterWidget : public QWidget
{
    Q_OBJECT

    public:
	PainterWidget(char  *picturename, QWidget *parent = 0);

    protected:
	void paintEvent(QPaintEvent*);

    private:
	QImage qimg;   
	char *picturename;       
};
#endif
