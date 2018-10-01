#ifndef MODEL_H
#define MODEL_H
#include <QWidget>
#include <QApplication>
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QImage>
#include <QFont>
#include <QObject>
#include <QTimer>
#include <PainterWidget.h>

class Model : public QWidget {
		Q_OBJECT
 
	public:
		Model(QWidget *parent = 0);
 
	public slots:
		void pushstart();
		void pushpre();
		void pushnext(); 
		void timeout();
    protected:
        void paintEvent(QPaintEvent *);



	private:
 		PainterWidget *img;
         	QPushButton *bstart;
         	QPushButton *bnext;
         	QPushButton *bpre;
        	QLabel *lbl;
		QTimer *timer;
          	int index, num, i, j;
		char input[5][30];
};
 
#endif

