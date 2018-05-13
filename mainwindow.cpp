#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->radiusSetter,SIGNAL(valueChanged(int)),this,SLOT(setNewRadius()));
  connect(ui->circleRadiusSetter,SIGNAL(valueChanged(int)),this,SLOT(setNewCircleRadius()));
  connect(ui->setRadius,SIGNAL(clicked(bool)),this,SLOT(resetPaintArea()));
  connect(ui->addCircle,SIGNAL(clicked(bool)),this,SLOT(addCircle()));
  connect(ui->cmpChecker,SIGNAL(clicked(bool)),this,SLOT(setCmpValue()));
  connect(ui->performanceTest,SIGNAL(clicked(bool)),this,SLOT(runPerformanceTest()));
  ui->radiusSetter->setValue(35);
  ui->circleRadiusSetter->setValue(15);
  resetPaintArea();
  r=(lineNum/2-1);
  colorList.push_back(QColor(225,0,0));
  colorList.push_back(QColor(0,225,0));
  colorList.push_back(QColor(0,0,225));
  colorList.push_back(QColor(255,255,0));
  colorList.push_back(QColor(0,255,255));
  colorList.push_back(QColor(255,0,255));
  drawAlgorithm=0;

}

MainWindow::~MainWindow()
{
  delete ui;
}
void MainWindow::drawPointAt(int x, int y, QPainter &painter,QColor color){
  QBrush tempBrush(color,Qt::SolidPattern);
  painter.setBrush(tempBrush);
  int realX=startX+gap*(x+r);
  int realY=startY+gap*(r-y);
  painter.drawRect(realX,realY,gap,gap);

}
void MainWindow::setNewRadius(){
  tempRadius=ui->radiusSetter->value();
  ui->radius->setText(QString("画板半径:")+QString::number(tempRadius));
}
void MainWindow::setCmpValue(){
  cmp=ui->cmpChecker->isChecked();
  this->repaint();
}

void MainWindow::setNewCircleRadius(){
  tempCircleRadius=ui->circleRadiusSetter->value();
  ui->circleRadius->setText(QString("圆半径:")+QString::number(tempCircleRadius));
}
void MainWindow::resetPaintArea(){
  r=tempRadius;
  lineNum=2*(r+1);
  boxWidth=gap*(lineNum-1);
  this->setFixedHeight(30*2+boxWidth);
  this->setFixedWidth(30+boxWidth+150);
  ui->radiusSetter->setGeometry(30+boxWidth+30,20,22,120);
  ui->setRadius->setGeometry(30+boxWidth+50,100,80,32);
  ui->radius->setGeometry(30+boxWidth+60,30,75,16);

  ui->circleRadiusSetter->setMaximum(r);
  ui->circleRadiusSetter->setGeometry(30+boxWidth+30,150,22,120);
  ui->addCircle->setGeometry(30+boxWidth+50,240,80,32);
  ui->circleRadius->setGeometry(30+boxWidth+60,160,75,16);
  ui->cmpChecker->setGeometry(30+boxWidth+30,280,91,20);
  ui->original->setGeometry(30+boxWidth+30,310,100,20);
  ui->integer->setGeometry(30+boxWidth+30,340,100,20);
  ui->optimized->setGeometry(30+boxWidth+30,370,100,20);
  ui->performanceTest->setGeometry(30+boxWidth+30,400,110,32);
}
void MainWindow::addCircle(){
  circles.push_back(tempCircleRadius);
  this->repaint();
}
void MainWindow::drawCircleWithRadius(int r,QPainter &painter,QColor color){
  if(r>this->r)return;
  int x=0;
  int y=r;
  double delta=1.25-r;
  while(y>=x){
      //draw
      drawPointAt(x,y,painter,color);
      drawPointAt(-x,y,painter,color);
      drawPointAt(x,-y,painter,color);
      drawPointAt(-x,-y,painter,color);
      drawPointAt(y,x,painter,color);
      drawPointAt(-y,x,painter,color);
      drawPointAt(y,-x,painter,color);
      drawPointAt(-y,-x,painter,color);
      if(delta<0){
          delta+=2*x+3.0;
        }else{
          delta+=2*(x-y)+5.0;
          --y;
        }
      ++x;
    }
}
void MainWindow::drawCircleWithRadiusPolar(int r, QPainter &painter, QColor color){
  if(r>this->r)return;
  for(float i=0.01;i<=6.28;i=i+0.01){
      drawPointAt(r*cos(i),r*sin(i),painter,color);
    }
}

void MainWindow::drawCircleWithRadiusInteger(int r, QPainter &painter, QColor color){
  if(r>this->r)return;
  int x=0;
  int y=r;
  int delta=1-r;
  //draw
  while(y>=x){
      //draw
      drawPointAt(x,y,painter,color);
      drawPointAt(-x,y,painter,color);
      drawPointAt(x,-y,painter,color);
      drawPointAt(-x,-y,painter,color);
      drawPointAt(y,x,painter,color);
      drawPointAt(-y,x,painter,color);
      drawPointAt(y,-x,painter,color);
      drawPointAt(-y,-x,painter,color);
      if(delta<0){
          delta+=2*x+3;
        }else{
          delta+=2*(x-y)+5;
          --y;
        }
      ++x;
    }
}


void MainWindow::drawCircleWithRadiusIntegerOptimized(int r, QPainter &painter, QColor color){
  if(r>this->r)return;
  int x=0;
  int y=r;
  int delta=1-r;
  int delta_t=3;
  int delta_b=-2*r+5;
  while(y>=x){
      //draw
      drawPointAt(x,y,painter,color);
      drawPointAt(-x,y,painter,color);
      drawPointAt(x,-y,painter,color);
      drawPointAt(-x,-y,painter,color);
      drawPointAt(y,x,painter,color);
      drawPointAt(-y,x,painter,color);
      drawPointAt(y,-x,painter,color);
      drawPointAt(-y,-x,painter,color);
      if(delta<0){
          delta+=delta_t;
          delta_t+=2;
          delta_b+=2;
        }else{
          delta+=delta_b;
          delta_t+=2;
          delta_b+=4;
          --y;
        }
      ++x;
    }
}

void MainWindow::paintEvent(QPaintEvent *event){
  QPainter painter(this);
      // 反走样
      painter.setRenderHint(QPainter::Antialiasing, true);
      // 设置画笔颜色
      QPen tempPen(QColor(0, 160, 230));
      tempPen.setWidth(3);
      //绘制外边框
      painter.setPen(tempPen);
      const int boardOffset=10;
      painter.drawLine(startX-boardOffset,startY-boardOffset,startX+boardOffset+boxWidth,startY-boardOffset);
      painter.drawLine(startX-boardOffset,startY+boxWidth+boardOffset,startX+boardOffset+boxWidth,startY+boardOffset+boxWidth);
      painter.drawLine(startX-boardOffset,startY-boardOffset,startX-boardOffset,startY+boardOffset+boxWidth);
      painter.drawLine(startX+boardOffset+boxWidth,startY-boardOffset,startX+boxWidth+boardOffset,startY+boardOffset+boxWidth);



      //绘制棋盘
      tempPen.setWidth(1);
      painter.setPen(tempPen);
      // 绘制直线

      for(int i=0;i<lineNum;++i){
          painter.drawLine(startX,startY+i*gap,startX+boxWidth,startY+i*gap);
        }
      for(int j=0;j<lineNum;++j){
          painter.drawLine(startX+j*gap,startY,startX+j*gap,startY+boxWidth);
        }
      drawPointAt(0,0,painter);
//      drawCircleWithRadius(12,painter);
      int counter=0;
      int colorListSize=colorList.size();
      int zeroX=startX+gap*r+gap/2;
      int zeroY=startY+gap*r+gap/2;
      QPoint center(zeroX,zeroY);

      if(isTesting){
          QTime startTime;
          startTime.start();
          for(auto &c:testCircles){
              if(drawAlgorithm==0)
//                drawCircleWithRadius(c,painter,colorList.at(counter++%colorListSize));
                drawCircleWithRadiusInteger(c,painter,colorList.at(counter++%colorListSize));
              else if(drawAlgorithm==1)
                drawCircleWithRadiusPolar(c,painter,colorList.at(counter++%colorListSize));
              else
                drawCircleWithRadiusIntegerOptimized(c,painter,colorList.at(counter++%colorListSize));
            }
          isTesting=false;
          QMessageBox::about(this,tr("绘图完成"),tr("绘制4000个圆耗时")+QString::number(startTime.elapsed())+tr("ms"));
          return;
        }

      for(auto &c:circles){
          if(drawAlgorithm==0)
            drawCircleWithRadiusInteger(c,painter,colorList.at(counter++%colorListSize));
          else if(drawAlgorithm==1)
            drawCircleWithRadiusPolar(c,painter,colorList.at(counter++%colorListSize));
          else
            drawCircleWithRadiusIntegerOptimized(c,painter,colorList.at(counter++%colorListSize));
        }
      if(cmp){
          QPen blackPen(QColor(0,0,0));
          painter.setPen(blackPen);
          painter.setBrush(Qt::NoBrush);
      for(auto &c:circles){
          if(c>r)continue;
              painter.drawEllipse(center,c*gap,c*gap);
        }
      }
}
void MainWindow::runPerformanceTest(){
  isTesting=true;
  testCircles.clear();
  for(int i=1;i<=4000;++i){
      testCircles.push_back(i%r);
    }
  this->repaint();
}

void MainWindow::on_original_clicked(bool checked)
{
    drawAlgorithm=0;
}

void MainWindow::on_integer_clicked(bool checked)
{
    drawAlgorithm=1;
}

void MainWindow::on_optimized_clicked(bool checked)
{
    drawAlgorithm=2;
}
