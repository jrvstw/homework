#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>

class myWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit myWidget(char *pics, int period, QWidget *parent = 0);

    public slots:
        void timeout();

    protected:
        void paintEvent(QPaintEvent *);

    private:
        char    *source;
        int     index;
        QTimer  *timer;

        // test files below
        char    test[5][30];
        //char    xml[5][30];
};

#endif //MYWIDGET_H
