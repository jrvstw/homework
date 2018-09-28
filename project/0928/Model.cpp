#include <Model.h>
#include <stdio.h>
#include <stdlib.h>
 
Model::Model(QWidget *parent) : QWidget(parent)
{
	//宣告繪圖物件顯示圖片
	strcpy(input[0], "impact51.jpg");
	strcpy(input[1], "impact52.jpg");
	strcpy(input[2], "impact53.jpg");
	strcpy(input[3], "impact54.jpg");
	strcpy(input[4], "water1.jpg");
	img  = new PainterWidget(input[0], this);
 	img->resize(1024, 600);
	
 
	index = 0;
	num = 0;
 	i=0;
	j=0;


	//主視窗畫布資訊及大小
        this->setWindowTitle("Demo");
	//this->showFullScreen();
        this->resize(1400,900);
 
 	//Label物件
        //lbl = new QLabel(this);
        //lbl->setText("Picture test program" );
        //lbl->setFont(QFont("Courier", 18, QFont::Bold));
        //lbl->setGeometry(50,240,220,50);

 	//Pushbutton物件
        //bnext = new QPushButton(this);
        //bnext->setText(">>");
        //bnext->setFont(QFont("Courier", 18, QFont::Bold));
        //bnext->setGeometry(215,310,50,50);
	//QObject::connect(bnext, SIGNAL(clicked()), this, SLOT(pushnext())); 

	//Timer物件
	timer = new QTimer(this);
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
	timer->start(2000);

  }
 
void Model::timeout()
{
 	/* Your code here */	
	index = (index==4)? 0: index + 1;
	delete img;
	img = new PainterWidget(input[index], this);
	img->resize(1024,600);
	img->show();

	//////////////////////////////////////////////  test block
	//if(j==1){					
	//	lbl->setText("Hello~ everybody!!!" );
	//	j=0;
	//}
     	//else{
	//	lbl->setText("Picture test program" );
	//	j=1;
	//}
	///////////////////////////////////////////////
}

	//  "start"按鈕的事件觸發
void Model::pushstart(){

	/* Your code here */

}
	
	//  "<<"按鈕的事件觸發
void Model::pushpre(){

	/* Your code here */

}

	//  ">>"按鈕的事件觸發
void Model::pushnext(){
	
	 /*
	 if(i==0)
		index++;
	 index = (index % 4);
         	 
        switch(index)
        {
            case 0:
                img[0] = new PainterWidget("01.jpg", this);
                img[0]->resize(320, 240);
		img[0]->show();
		i=0;
                break;

            case 1:
                img[1] = new PainterWidget("02.jpg", this);
                img[1]->resize(320, 240);
		img[1]->show();
		i=0;
                break;

            case 2:
                img[2] = new PainterWidget("03.jpg", this);
                img[2]->resize(320, 240);
		img[2]->show();
		i=0;
                break;

            case 3:
                img[3] = new PainterWidget("04.jpg", this);
                img[3]->resize(320, 240);
		img[3]->show();
		i=0;
                break;

            default:
                break;
	    i=0;
   }
*/
}


