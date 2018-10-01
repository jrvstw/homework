#include <QApplication>
#include "myWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    char source[30];
    int  period = 1000; // millisecond.
    strcpy(source, "../pics/impact51.jpg");

    myWidget *defectLocator = new myWidget(source, period);
    defectLocator->resize(1024,600);
    defectLocator->show();

    return app.exec();
}
