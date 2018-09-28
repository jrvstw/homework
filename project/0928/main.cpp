#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QImage>
#include <QFont>
#include <QObject>
#include <Model.h>
#include "PainterWidget.h"



int main(int argc, char *argv[]) 
{
	QApplication app(argc, argv);
	
	Model *widget = new Model;

	widget->show();
     
	return app.exec();
}


