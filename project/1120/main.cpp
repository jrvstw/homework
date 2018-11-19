#include <cstring>
#include <QApplication>
#include "myWidget.h"

void import_pics(char source[][30]);
void import_xmls(char xmlFile[][30]);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    int  nSource = 20;
    char source[20][30];
    char xmlFile[20][30];
    import_pics(source);
    import_xmls(xmlFile);
    int  period = 0; // millisec.

    myWidget *defectLocator = new myWidget(xmlFile, source, nSource, period);
    //defectLocator->resize(960,540);
    defectLocator->showFullScreen();
    defectLocator->show();

    return app.exec();
}

void import_pics(char source[][30])
{
    strcpy(source[ 0], "../pics/impact51.jpg");
    strcpy(source[ 1], "../pics/impact52.jpg");
    strcpy(source[ 2], "../pics/impact53.jpg");
    strcpy(source[ 3], "../pics/impact54.jpg");
    strcpy(source[ 4], "../pics/impact55.jpg");
    strcpy(source[ 5], "../pics/scratch271.jpg");
    strcpy(source[ 6], "../pics/scratch272.jpg");
    strcpy(source[ 7], "../pics/scratch273.jpg");
    strcpy(source[ 8], "../pics/scratch274.jpg");
    strcpy(source[ 9], "../pics/scratch275.jpg");
    strcpy(source[10], "../pics/sponge457.jpg");
    strcpy(source[11], "../pics/sponge458.jpg");
    strcpy(source[12], "../pics/sponge459.jpg");
    strcpy(source[13], "../pics/sponge460.jpg");
    strcpy(source[14], "../pics/sponge461.jpg");
    strcpy(source[15], "../pics/water1.jpg");
    strcpy(source[16], "../pics/water2.jpg");
    strcpy(source[17], "../pics/water3.jpg");
    strcpy(source[18], "../pics/water4.jpg");
    strcpy(source[19], "../pics/water5.jpg");
}

void import_xmls(char xmlFile[][30])
{
    strcpy(xmlFile[ 0], "../xml/impact51.xml");
    strcpy(xmlFile[ 1], "../xml/impact52.xml");
    strcpy(xmlFile[ 2], "../xml/impact53.xml");
    strcpy(xmlFile[ 3], "../xml/impact54.xml");
    strcpy(xmlFile[ 4], "../xml/impact55.xml");
    strcpy(xmlFile[ 5], "../xml/scratch271.xml");
    strcpy(xmlFile[ 6], "../xml/scratch272.xml");
    strcpy(xmlFile[ 7], "../xml/scratch273.xml");
    strcpy(xmlFile[ 8], "../xml/scratch274.xml");
    strcpy(xmlFile[ 9], "../xml/scratch275.xml");
    strcpy(xmlFile[10], "../xml/sponge457.xml");
    strcpy(xmlFile[11], "../xml/sponge458.xml");
    strcpy(xmlFile[12], "../xml/sponge459.xml");
    strcpy(xmlFile[13], "../xml/sponge460.xml");
    strcpy(xmlFile[14], "../xml/sponge461.xml");
    strcpy(xmlFile[15], "../xml/water1.xml");
    strcpy(xmlFile[16], "../xml/water2.xml");
    strcpy(xmlFile[17], "../xml/water3.xml");
    strcpy(xmlFile[18], "../xml/water4.xml");
    strcpy(xmlFile[19], "../xml/water5.xml");
}
